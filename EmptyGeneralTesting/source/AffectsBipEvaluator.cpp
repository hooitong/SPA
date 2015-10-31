#include "AffectsBipEvaluator.h"
#include <algorithm>
#include <iterator>

AffectsBipEvaluator::AffectsBipEvaluator(PKB* p) { pkb = p; }

QueryResult AffectsBipEvaluator::evaluate(QNode* node) {
  QNode* leftChild = node->getChildren()[0];
  QNode* rightChild = node->getChildren()[1];

  if (leftChild->getQType() == ANY &&
    rightChild->getQType() == ANY) {
    return QueryResult(solveAnyAny());
  }
  else if (leftChild->getQType() == ANY &&
    isSynonym(rightChild->getQType())) {
    return QueryResult(solveAnySyn(), rightChild->getString());
  }
  else if (leftChild->getQType() == ANY &&
    rightChild->getQType() == CONST) {
    return QueryResult(solveAnyConst(getInteger(rightChild)));
  }
  else if (isSynonym(leftChild->getQType()) &&
    rightChild->getQType() == ANY) {
    return QueryResult(solveSynAny(), leftChild->getString());
  }
  else if (isSynonym(leftChild->getQType()) &&
    isSynonym(rightChild->getQType())) {
    return QueryResult(solveSynSyn(), leftChild->getString(), rightChild->getString());
  }
  else if (isSynonym(leftChild->getQType()) &&
    rightChild->getQType() == CONST) {
    return QueryResult(solveSynConst(getInteger(rightChild)), leftChild->getString());
  }
  else if (leftChild->getQType() == CONST &&
    rightChild->getQType() == ANY) {
    return QueryResult(solveConstAny(getInteger(leftChild)));
  }
  else if (leftChild->getQType() == CONST &&
    isSynonym(rightChild->getQType())) {
    return QueryResult(solveConstSyn(getInteger(leftChild)), rightChild->getString());
  }
  else if (leftChild->getQType() == CONST &&
    rightChild->getQType() == CONST) {
    return QueryResult(solveConstConst(getInteger(leftChild), getInteger(rightChild)));
  }
}

bool AffectsBipEvaluator::solveConstConst(const int left, const int right) {
  AST *ast = pkb->getAst();

  /* Left and Right are Statement Lines */
  /* Check that both statement lines are assignment statements */
  if (ast->getTNode(left)->getTType() != ASSIGNN || ast->getTNode(right)->getTType() != ASSIGNN) return false;

  /* Check that both are modifying and using the same variable and save variable */
  VARINDEX contextVar = pkb->getModifies()->getModifiedByStmt(left)[0];
  vector<VARINDEX> usedVars = pkb->getUses()->getUsedByStmt(right);
  if (std::find(usedVars.begin(), usedVars.end(), contextVar) == usedVars.end()) return false;

  /* Check that there is a control path from left to right */
  if (!pkb->getNextBip()->isNextStar(left, right)) return false;

  /* Heavy computation alert! Using Next table, check the statement lines whether other variable modifies it */
  return findConstToConst(left, right, contextVar, std::vector<STMTLINE>(), std::stack<STMTLINE>());
}

vector<int> AffectsBipEvaluator::solveConstSyn(const int left) {
  /* Check if left is valid */
  if (pkb->getAst()->getTNode(left)->getTType() != ASSIGNN) return vector<int>();

  /* Retrieve context variable from left */
  VARINDEX contextVar = pkb->getModifies()->getModifiedByStmt(left)[0];

  /* Retrieve all statements reached by left */
  vector<STMTLINE> possibleRight = pkb->getNext()->getNextStar(left);

  /* Filter the reachable statements to valid assignment statements */
  set<STMTLINE> validCandidates, returnedCandidates;
  for (int i = 0; i < possibleRight.size(); i++) {
    if (isRightCandidate(possibleRight[i], contextVar)) {
      validCandidates.insert(possibleRight[i]);
      returnedCandidates.insert(possibleRight[i]);
    }
  }

  /* Execute path searching algorithm for Affects */
  findSynonymFromConst(left, contextVar, &returnedCandidates, std::vector<STMTLINE>(), false, std::stack<STMTLINE>());

  /* Find the difference between the sets */
  vector<STMTLINE> results;
  std::set_difference(validCandidates.begin(), validCandidates.end(), returnedCandidates.begin(), returnedCandidates.end(),
    std::inserter(results, results.end()));

  return results;
}

vector<int> AffectsBipEvaluator::solveSynConst(const int right) {
  /* Check if left is valid */
  if (pkb->getAst()->getTNode(right)->getTType() != ASSIGNN) return std::vector<int>();

  /* Retrieve context variable from right */
  vector<VARINDEX> contextVars = pkb->getUses()->getUsedByStmt(right);

  /* Retrieve all statements that can reach to right */
  vector<STMTLINE> possibleLeft = pkb->getNext()->getBeforeStar(right);

  /* Filter the reachable statements to valid assignment statements */
  set<STMTLINE> validCandidates, returnedCandidates;
  for (int i = 0; i < possibleLeft.size(); i++) {
    if (isLeftCandidate(possibleLeft[i], contextVars)) {
      validCandidates.insert(possibleLeft[i]);
      returnedCandidates.insert(possibleLeft[i]);
    }
  }

  /* Execute path searching algorithm for Affects */
  findSynonymToConst(right, std::set<STMTLINE>(contextVars.begin(), contextVars.end()), &returnedCandidates, std::vector<STMTLINE>(), false, std::stack<STMTLINE>());

  /* Find the difference between the sets */
  vector<STMTLINE> results;
  std::set_difference(validCandidates.begin(), validCandidates.end(), returnedCandidates.begin(), returnedCandidates.end(),
    std::inserter(results, results.end()));

  return results;
}

vector<std::pair<int, int>> AffectsBipEvaluator::solveSynSyn() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  vector<std::pair<int, int>>  tupleResults;
  for (int i = 0; i < allAssign.size(); i++) {
    vector<int> rightValues = solveConstSyn(allAssign[i]);
    for (int j = 0; j < rightValues.size(); j++) {
      tupleResults.push_back(make_pair(allAssign[i], rightValues[j]));
    }
  }

  return tupleResults;
}

vector<int> AffectsBipEvaluator::solveAnySyn() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  vector<int>  rightResults;
  for (int i = 0; i < allAssign.size(); i++) {
    vector<int> rightValues = solveConstSyn(allAssign[i]);
    rightResults.insert(rightResults.end(), rightValues.begin(), rightValues.end());
  }

  return *(removeDuplicate(&rightResults));
}

vector<int> AffectsBipEvaluator::solveSynAny() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  vector<int>  leftResults;
  for (int i = 0; i < allAssign.size(); i++) {
    vector<int> leftValues = solveSynConst(allAssign[i]);
    leftResults.insert(leftResults.end(), leftValues.begin(), leftValues.end());
  }

  return *(removeDuplicate(&leftResults));
}

bool AffectsBipEvaluator::solveAnyConst(const int right) {
  /* Check if left is valid */
  if (pkb->getAst()->getTNode(right)->getTType() != ASSIGNN) return false;

  /* Retrieve context variable from right */
  vector<VARINDEX> contextVars = pkb->getUses()->getUsedByStmt(right);

  /* Retrieve all statements that can reach to right */
  vector<STMTLINE> possibleLeft = pkb->getNext()->getBeforeStar(right);

  /* Filter the reachable statements to valid assignment statements */
  set<STMTLINE> validCandidates, returnedCandidates;
  for (int i = 0; i < possibleLeft.size(); i++) {
    if (isLeftCandidate(possibleLeft[i], contextVars)) {
      validCandidates.insert(possibleLeft[i]);
      returnedCandidates.insert(possibleLeft[i]);
    }
  }

  /* Execute path searching algorithm for Affects */
  return findSynonymToConst(right, set<STMTLINE>(contextVars.begin(), contextVars.end()), &returnedCandidates, 
    std::vector<STMTLINE>(), true, std::stack<STMTLINE>());
}

bool AffectsBipEvaluator::solveConstAny(const int left) {
  /* Check if left is valid */
  if (pkb->getAst()->getTNode(left)->getTType() != ASSIGNN) return false;

  /* Retrieve context variable from left */
  VARINDEX contextVar = pkb->getModifies()->getModifiedByStmt(left)[0];

  /* Retrieve all statements reached by left */
  vector<STMTLINE> possibleRight = pkb->getNext()->getNextStar(left);

  /* Filter the reachable statements to valid assignment statements */
  set<STMTLINE> validCandidates, returnedCandidates;
  for (int i = 0; i < possibleRight.size(); i++) {
    if (isRightCandidate(possibleRight[i], contextVar)) {
      validCandidates.insert(possibleRight[i]);
      returnedCandidates.insert(possibleRight[i]);
    }
  }

  /* Execute path searching algorithm for Affects */
  return findSynonymFromConst(left, contextVar, &returnedCandidates, std::vector<STMTLINE>(), true, std::stack<STMTLINE>());
}

bool AffectsBipEvaluator::solveAnyAny() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  for (int i = 0; i < allAssign.size(); i++) {
    if (solveConstAny(allAssign[i])) return true;
  }
  return false;
}

bool AffectsBipEvaluator::findConstToConst(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path, std::stack<STMTLINE> previousCalls) {
  /* Base Case */
  if (current == end) return true;

  /* Early terminate if this stmtline cannot reach end path */
  if (!pkb->getNextBip()->isNextStar(current, end)) return false;

  /* Check cyclic in path */
  if (std::find(path.begin(), path.end(), current) != path.end()) return false;

  /* Check current stmtline whether it modifies variable */
  TType currentType = pkb->getAst()->getTNode(current)->getTType();
  if (path.size() != 0 && current != end && currentType == ASSIGNN &&
    pkb->getModifies()->isModifiesForStmt(current, contextVar)) return false;


  /* Get all possible next path and navigate recursively */
  vector<STMTLINE> allNext = pkb->getNextBip()->getNext(current);
  bool isEndStatement = pkb->getNext()->getNext(current).empty();
  bool pathsStatus = false;
  path.push_back(current);

  /* If current statement is a CALL statement then traverse with next line in stack to next procedure */
  if (currentType == CALLN) {
    if (!isEndStatement) previousCalls.push(pkb->getNext()->getNext(current)[0]);
    pathsStatus = findConstToConst(allNext[0], end, contextVar, path, previousCalls);
  }

  /* This denotes that it reaches end of the procedure, time to return to correct procedure stack */
  else if (isEndStatement && !previousCalls.empty()) {
    STMTLINE returnIndex = previousCalls.top();
    previousCalls.pop();
    pathsStatus = findConstToConst(returnIndex, end, contextVar, path, previousCalls);
  } 
  
  /* Traverse to all possible paths and navigate recursively that are within same procedure */
  else {
    for (int i = 0; i < allNext.size(); i++) {
      pathsStatus = pathsStatus | findConstToConst(allNext[i], end, contextVar, path, previousCalls);
    }
  }

  return pathsStatus;
}

bool AffectsBipEvaluator::findSynonymFromConst(STMTLINE current, VARINDEX contextVar, set<STMTLINE> *candidates, vector<STMTLINE> path, bool takeAny, std::stack<STMTLINE> previousCalls) {
  /* If no more candidates, return to reduce computation */
  if (candidates->size() == 0) return false;

  /* Assertion: Assume that candidates are all valid ones (Assign Statements/Same Context) */
  /* Remove current line from candidates if exist */
  bool isCandidate = candidates->erase(current);
  /* Short circuited statement to reduce computation */
  if (isCandidate && takeAny) return true;

  /* Check cyclic in path */
  if (std::find(path.begin(), path.end(), current) != path.end()) return false;

  /* Check if path can be progressed */
  /* Check current stmtline whether it modifies variable */
  TType currentType = pkb->getAst()->getTNode(current)->getTType();
  if (path.size() != 0 && currentType == ASSIGNN
    && pkb->getModifies()->isModifiesForStmt(current, contextVar)) return false;

  /* Get all possible next path and navigate recursively */
  vector<STMTLINE> allNext = pkb->getNext()->getNext(current);
  bool isEndStatement = pkb->getNext()->getNext(current).empty();
  bool pathsStatus = false;
  path.push_back(current);

  /* If current statement is a CALL statement then traverse with next line in stack to next procedure */
  if (currentType == CALLN) {
    if (!isEndStatement) previousCalls.push(pkb->getNext()->getNext(current)[0]);
    if (findSynonymFromConst(allNext[0], contextVar, candidates, path, takeAny, previousCalls)) {
      pathsStatus = true;
    }
  }

  /* This denotes that it reaches end of the procedure, time to return to correct procedure stack */
  else if (isEndStatement && !previousCalls.empty()) {
    STMTLINE returnIndex = previousCalls.top();
    previousCalls.pop();
    if (findSynonymFromConst(returnIndex, contextVar, candidates, path, takeAny, previousCalls)) {
      pathsStatus = true;
    }
  }

  /* Traverse to all possible paths and navigate recursively that are within same procedure */
  else {
    for (int i = 0; i < allNext.size(); i++) {
      if (findSynonymFromConst(allNext[i], contextVar, candidates, path, takeAny, previousCalls)) {
        if (takeAny) return true;
        pathsStatus = true;
      }
    }
  }

  return pathsStatus;
}

bool AffectsBipEvaluator::findSynonymToConst(STMTLINE current, set<VARINDEX> contextVar, set<STMTLINE> *candidates, vector<STMTLINE> path, bool takeAny, std::stack<STMTLINE> previousCalls) {
  /* If no more candidates, return to reduce computation */
  if (candidates->size() == 0) return false;

  /* Assertion: Assume that candidates are all assign statements */
  if (candidates->find(current) != candidates->end()) {
    /* Check whether the candidate is still a valid one found in contextVar */
    VARINDEX modifiedVar = pkb->getModifies()->getModifiedByStmt(current)[0];
    if (contextVar.find(modifiedVar) != contextVar.end()) {
      /* Remove current line from candidates if exist */
      bool isCandidate = candidates->erase(current);
      /* Short circuited statement to reduce computation */
      if (isCandidate && takeAny) return true;
    }
  }

  /* Check cyclic in path */
  if (std::find(path.begin(), path.end(), current) != path.end()) return false;

  /* Check if path can be progressed */
  /* Check current stmtline whether it modifies variable */
  TType currentType = pkb->getAst()->getTNode(current)->getTType();
  bool isNotOrigin = path.size() != 0;

  if (isNotOrigin && currentType == ASSIGNN) {
    vector<VARINDEX> modifiedVars = pkb->getModifies()->getModifiedByStmt(current);
    set<VARINDEX> modifiedSet(modifiedVars.begin(), modifiedVars.end());

    /* Removed modifiedVars from contextVar */
    set<VARINDEX> resultingSet;
    std::set_difference(contextVar.begin(), contextVar.end(), modifiedSet.begin(), modifiedSet.end(),
      std::inserter(resultingSet, resultingSet.end()));
    /* If all variables are block, just return */
    if (resultingSet.size() == 0) return false;
    contextVar = resultingSet;
  }

  /* Get all possible before path and navigate recursively */
  vector<STMTLINE> allBefore = pkb->getNext()->getBefore(current);
  bool isStartStatement = pkb->getNext()->getBefore(current).empty();
  bool pathsStatus = false;
  path.push_back(current);


  /* If current statement is a CALL statement then traverse with next line in stack to next procedure */
  if (currentType == CALLN) {
    if (!isStartStatement) previousCalls.push(pkb->getNext()->getBefore(current)[0]);
    if (findSynonymToConst(allBefore[0], contextVar, candidates, path, takeAny, previousCalls)) {
      pathsStatus = true;
    }
  }

  /* This denotes that it reaches start of the procedure, time to return to correct procedure stack */
  else if (isStartStatement && !previousCalls.empty()) {
    STMTLINE returnIndex = previousCalls.top();
    previousCalls.pop();
    if (findSynonymToConst(returnIndex, contextVar, candidates, path, takeAny, previousCalls)) {
      pathsStatus = true;
    }
  }

  /* Traverse to all possible paths and navigate recursively that are within same procedure */
  else {
    for (int i = 0; i < allBefore.size(); i++) {
      if (findSynonymToConst(allBefore[i], contextVar, candidates, path, takeAny, previousCalls)) {
        if (takeAny) return true;
        pathsStatus = true;
      }
    }
  }

  return pathsStatus;
}

int AffectsBipEvaluator::getInteger(QNode* node) {
  std::istringstream iss(node->getString());
  int result;
  iss >> result;
  return result;
}

bool AffectsBipEvaluator::isSynonym(QNodeType type) {
  return type == WHILESYNONYM ||
    type == ASSIGNSYNONYM ||
    type == VARIABLESYNONYM ||
    type == PROCEDURESYNONYM ||
    type == CONSTSYNONYM ||
    type == PROGLINESYNONYM ||
    type == IFSYNONYM ||
    type == STMTSYNONYM;
}

bool AffectsBipEvaluator::isConst(QNodeType type) {
  return type == CONST || type == VAR;
}

bool AffectsBipEvaluator::isLeftCandidate(STMTLINE current, vector<VARINDEX> contextVars) {
  if (pkb->getAst()->getTNode(current)->getTType() != ASSIGNN) return false;

  /* Check if possible candidate modifies any variable in contextVars */
  return std::find(contextVars.begin(), contextVars.end(), pkb->getModifies()->getModifiedByStmt(current)[0]) != contextVars.end();
}

bool AffectsBipEvaluator::isRightCandidate(STMTLINE current, VARINDEX contextVar) {
  if (pkb->getAst()->getTNode(current)->getTType() != ASSIGNN) return false;

  /* Check if possible candidate uses any variable in contextVars */
  vector<VARINDEX> usedVariables = pkb->getUses()->getUsedByStmt(current);
  return std::find(usedVariables.begin(), usedVariables.end(), contextVar) != usedVariables.end();
}


vector<int>* AffectsBipEvaluator::removeDuplicate(vector<int>* v) {
  /* Remove duplicates using sets */
  set<int> s(v->begin(), v->end());
  v->assign(s.begin(), s.end());
  return v;
}