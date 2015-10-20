#include "AffectsEvaluator.h"
#include <algorithm>
#include <iterator>

AffectsEvaluator::AffectsEvaluator(PKB* p) { pkb = p; }

QueryResult AffectsEvaluator::evaluate(QNode* node) {
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

bool AffectsEvaluator::solveConstConst(const int left, const int right) {
  AST *ast = pkb->getAst();

  /* Left and Right are Statement Lines */
  /* Check that both statement lines are assignment statements */
  if (ast->getTNode(left)->getTType() != ASSIGNN || ast->getTNode(right)->getTType() != ASSIGNN) return false;

  /* Check that both are modifying and using the same variable and save variable */
  VARINDEX contextVar = pkb->getModifies()->getModifiedByStmt(left)[0];
  vector<VARINDEX> usedVars = pkb->getUses()->getUsedByStmt(right);
  if (std::find(usedVars.begin(), usedVars.end(), contextVar) == usedVars.end()) return false;

  /* Check that there is a control path from left to right */
  if (!pkb->getNext()->isNextStar(left, right)) return false;

  /* Heavy computation alert! Using Next table, check the statement lines whether other variable modifies it */
  vector<STMTLINE> path;
  return findConstToConst(left, right, contextVar, path);
}

vector<int> AffectsEvaluator::solveConstSyn(const int left) {
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
  findSynonymFromConst(left, contextVar, &returnedCandidates, vector<STMTLINE>(), false);

  /* Find the difference between the sets */
  vector<STMTLINE> results;
  std::set_difference(validCandidates.begin(), validCandidates.end(), returnedCandidates.begin(), returnedCandidates.end(),
    std::inserter(results, results.end()));

  return results;
}

vector<int> AffectsEvaluator::solveSynConst(const int right) {
  /* Check if left is valid */
  if (pkb->getAst()->getTNode(right)->getTType() != ASSIGNN) return vector<int>();

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
  findSynonymToConst(right, set<STMTLINE>(contextVars.begin(), contextVars.end()), &returnedCandidates, vector<STMTLINE>(), false);

  /* Find the difference between the sets */
  vector<STMTLINE> results;
  std::set_difference(validCandidates.begin(), validCandidates.end(), returnedCandidates.begin(), returnedCandidates.end(),
    std::inserter(results, results.end()));

  return results;
}

vector<std::pair<int, int>> AffectsEvaluator::solveSynSyn() {
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

vector<int> AffectsEvaluator::solveAnySyn() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  vector<int>  rightResults;
  for (int i = 0; i < allAssign.size(); i++) {
    vector<int> rightValues = solveConstSyn(allAssign[i]);
    rightResults.insert(rightResults.end(), rightValues.begin(), rightValues.end());
  }

  return *(removeDuplicate(&rightResults));
}

vector<int> AffectsEvaluator::solveSynAny() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  vector<int>  leftResults;
  for (int i = 0; i < allAssign.size(); i++) {
    vector<int> leftValues = solveSynConst(allAssign[i]);
    leftResults.insert(leftResults.end(), leftValues.begin(), leftValues.end());
  }

  return *(removeDuplicate(&leftResults));
}

bool AffectsEvaluator::solveAnyConst(const int right) {
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
  return findSynonymToConst(right, set<STMTLINE>(contextVars.begin(), contextVars.end()), &returnedCandidates, vector<STMTLINE>(), true);
}

bool AffectsEvaluator::solveConstAny(const int left) {
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
  return findSynonymFromConst(left, contextVar, &returnedCandidates, vector<STMTLINE>(), true);
}

bool AffectsEvaluator::solveAnyAny() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  for (int i = 0; i < allAssign.size(); i++) {
    if (solveConstAny(allAssign[i])) return true;
  }
  return false;
}

bool AffectsEvaluator::findConstToConst(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path) {
  /* Base Case */
  if (current == end) return true;

  /* Early terminate if this stmtline cannot reach end path */
  if (!pkb->getNext()->isNextStar(current, end)) return false;

  /* Check cyclic in path */
  if (std::find(path.begin(), path.end(), current) != path.end()) return false;

  /* Check current stmtline whether it modifies variable */
  TType currentType = pkb->getAst()->getTNode(current)->getTType();
  if (path.size() != 0 && current != end && (currentType == ASSIGNN || currentType == CALLN) &&
    pkb->getModifies()->isModifiesForStmt(current, contextVar)) return false;

  /* Get all possible next path and navigate recursively */
  vector<STMTLINE> allNext = pkb->getNext()->getNext(current);
  bool pathsStatus = false;
  path.push_back(current);

  for (int i = 0; i < allNext.size(); i++) {
    pathsStatus = pathsStatus | findConstToConst(allNext[i], end, contextVar, path);
  }

  return pathsStatus;
}

bool AffectsEvaluator::findSynonymFromConst(STMTLINE current, VARINDEX contextVar, set<STMTLINE> *candidates, vector<STMTLINE> path, bool takeAny) {
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
  if (path.size() != 0 && (currentType == ASSIGNN || currentType == CALLN)
    && pkb->getModifies()->isModifiesForStmt(current, contextVar)) return false;

  /* Get all possible next path and navigate recursively */
  vector<STMTLINE> allNext = pkb->getNext()->getNext(current);
  bool pathsStatus = false;
  path.push_back(current);
  for (int i = 0; i < allNext.size(); i++) {
    if (findSynonymFromConst(allNext[i], contextVar, candidates, path, takeAny)) {
      if (takeAny) return true;
      pathsStatus = true;
    }
  }

  return pathsStatus;
}

bool AffectsEvaluator::findSynonymToConst(STMTLINE current, set<VARINDEX> contextVar, set<STMTLINE> *candidates, vector<STMTLINE> path, bool takeAny) {
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

  if (isNotOrigin && (currentType == ASSIGNN || currentType == CALLN)) {
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
  bool pathsStatus = false;
  path.push_back(current);
  for (int i = 0; i < allBefore.size(); i++) {
    if (findSynonymToConst(allBefore[i], contextVar, candidates, path, takeAny)) {
      if (takeAny) return true;
      pathsStatus = true;
    }
  }

  return pathsStatus;
}

int AffectsEvaluator::getInteger(QNode* node) {
  std::istringstream iss(node->getString());
  int result;
  iss >> result;
  return result;
}

bool AffectsEvaluator::isSynonym(QNodeType type) {
  return type == WHILESYNONYM ||
    type == ASSIGNSYNONYM ||
    type == VARIABLESYNONYM ||
    type == PROCEDURESYNONYM ||
    type == CONSTSYNONYM ||
    type == PROGLINESYNONYM ||
    type == IFSYNONYM ||
    type == STMTSYNONYM;
}

bool AffectsEvaluator::isConst(QNodeType type) {
  return type == CONST || type == VAR;
}

bool AffectsEvaluator::isLeftCandidate(STMTLINE current, vector<VARINDEX> contextVars) {
  if (pkb->getAst()->getTNode(current)->getTType() != ASSIGNN) return false;

  /* Check if possible candidate modifies any variable in contextVars */
  return std::find(contextVars.begin(), contextVars.end(), pkb->getModifies()->getModifiedByStmt(current)[0]) != contextVars.end();
}

bool AffectsEvaluator::isRightCandidate(STMTLINE current, VARINDEX contextVar) {
  if (pkb->getAst()->getTNode(current)->getTType() != ASSIGNN) return false;

  /* Check if possible candidate uses any variable in contextVars */
  vector<VARINDEX> usedVariables = pkb->getUses()->getUsedByStmt(current);
  return std::find(usedVariables.begin(), usedVariables.end(), contextVar) != usedVariables.end();
}


vector<int>* AffectsEvaluator::removeDuplicate(vector<int>* v) {
  /* Remove duplicates using sets */
  set<int> s(v->begin(), v->end());
  v->assign(s.begin(), s.end());
  return v;
}