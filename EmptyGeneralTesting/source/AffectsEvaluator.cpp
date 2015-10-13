#include "AffectsEvaluator.h"
#include <algorithm>
#include <iostream>

/*
  TODO: Code is currently unoptimized and untested. Does not use result to compute as well.
*/

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
    return QueryResult(solveAnyConst(getInteger(leftChild)));
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
  bool isTypeCorrect = ast->getTNode(left)->getTType() == ASSIGNN && ast->getTNode(right)->getTType() == ASSIGNN;

  /* Check that both are modifying and using the same variable and save variable */
  /* TODO: Will crash if the statement does not modifies or uses */ 
  VARINDEX contextVar = pkb->getModifies()->getModifiedByStmt(left)[0];
  vector<VARINDEX> usedVars = pkb->getUses()->getUsedByStmt(right);
  bool isSameContext = std::find(usedVars.begin(), usedVars.end(), contextVar) != usedVars.end();

  /* Check that there is a control path from left to right */
  bool isContainsPath = pkb->getNext()->isNextStar(left, right);

  /* Heavy computation alert! Using Next table, check the statement lines whether other variable modifies it */
  vector<STMTLINE> path;
  bool isNotModifiedBetween = findPathToNode(left, right, contextVar, path);

  /* If all boolean is true then return true else false */
  return isTypeCorrect && isSameContext && isContainsPath && isNotModifiedBetween;
}

vector<int> AffectsEvaluator::solveConstSyn(const int left) {
  /* Retrieve all statements reached by left */
  vector<STMTLINE> possibleRight = pkb->getNext()->getNextStar(left);

  /* TODO: Lazy implementation by computing one by one */
  vector<STMTLINE> resultRight;
  for (int i = 0; i < possibleRight.size(); i++) {
    /* Only applies to assignment statements */
    if (pkb->getAst()->getTNode(possibleRight[i])->getTType() == ASSIGNN) {
      if (solveConstConst(left, possibleRight[i])) resultRight.push_back(possibleRight[i]);
    }
  }

  return resultRight;
}

vector<int> AffectsEvaluator::solveSynConst(const int right) {
  /* Retrieve all statements that can reach to right */
  vector<STMTLINE> possibleLeft = pkb->getNext()->getBeforeStar(right);

  /* TODO: Lazy implementation by computing one by one */
  vector<STMTLINE> resultLeft;
  for (int i = 0; i < possibleLeft.size(); i++) {
    /* Only applies to assignment statements */
    if (pkb->getAst()->getTNode(possibleLeft[i])->getTType() == ASSIGNN) {
      if (solveConstConst(right, possibleLeft[i])) resultLeft.push_back(possibleLeft[i]);
    }
  }

  return resultLeft;
}

vector<std::pair<int, int>> AffectsEvaluator::solveSynSyn() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  /* Terrible O(N^3) performance loops - Lazy Implementation */
  vector<std::pair<int, int>>  tupleResults;
  for (int i = 0; i < allAssign.size(); i++) {
    for (int j = 0; j < allAssign.size(); j++) {
      if (i == j) continue;
      if (solveConstConst(allAssign[i], allAssign[j]))
        tupleResults.push_back(make_pair(i, j));
    }
  }

  return tupleResults;
}

vector<int> AffectsEvaluator::solveAnySyn() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  /* Terrible O(N^3) performance loops - Lazy Implementation */
  vector<int>  rightResults;
  for (int i = 0; i < allAssign.size(); i++) {
    for (int j = 0; j < allAssign.size(); j++) {
      if (i == j) continue;
      if (solveConstConst(allAssign[i], allAssign[j]))
        rightResults.push_back(j);
    }
  }

  return rightResults;
}

vector<int> AffectsEvaluator::solveSynAny() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  /* Terrible O(N^3) performance loops - Lazy Implementation */
  vector<int>  leftResult;
  for (int i = 0; i < allAssign.size(); i++) {
    for (int j = 0; j < allAssign.size(); j++) {
      if (i == j) continue;
      if (solveConstConst(allAssign[i], allAssign[j]))
        leftResult.push_back(i);
    }
  }

  return leftResult;
}

bool AffectsEvaluator::solveAnyConst(const int right) {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  /* Terrible O(N^2) performance loops - Lazy Implementation */
  for (int i = 0; i < allAssign.size(); i++) {
    return solveConstConst(allAssign[i], right);
  }

  return false;
}

bool AffectsEvaluator::solveConstAny(const int left) {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  /* Terrible O(N^2) performance loops - Lazy Implementation */
  vector<int>  leftResult;
  for (int i = 0; i < allAssign.size(); i++) {
    return solveConstConst(left, allAssign[i]);
  }

  return false;
}

bool AffectsEvaluator::solveAnyAny() {
  /* Retrieve all assignment statement numbers in the program */
  vector<int> allAssign = pkb->getAst()->getStmtLines(ASSIGNN);

  /* Terrible O(N^3) performance loops - Lazy Implementation */
  vector<int>  leftResult;
  for (int i = 0; i < allAssign.size(); i++) {
    for (int j = 0; j < allAssign.size(); j++) {
      if (i == j) continue;
      if (solveConstConst(allAssign[i], allAssign[j]))
        return true;
    }
  }

  return false;
}

bool AffectsEvaluator::findPathToNode(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path) {
  /* Base Case */
  if (current == end) return true;

  /* Early terminate if this stmtline cannot reach end path */
  if (!pkb->getNext()->isNextStar(current, end)) return false;

  /* Check cyclic in path */
  if (std::find(path.begin(), path.end(), current) != path.end()) return false;

  /* Check current stmtline whether it modifies variable */
  if (path.size() != 0 && current != end && pkb->getAst()->getTNode(current)->getTType() == ASSIGNN && 
    pkb->getModifies()->isModifiesForStmt(current, contextVar)) return false;

  /* Get all possible next path and navigate recursively */
  vector<STMTLINE> allNext = pkb->getNext()->getNext(current);
  bool pathsStatus = false;
  path.push_back(current);

  for (int i = 0; i < allNext.size(); i++) {
    pathsStatus = pathsStatus || findPathToNode(allNext[i], end, contextVar, path);
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
  return type == CONST ||
    type == VAR;
}



TType AffectsEvaluator::synonymToTType(QNodeType type) {
  if (type == WHILESYNONYM) {
    return WHILEN;
  }
  else if (type == ASSIGNSYNONYM) {
    return ASSIGNN;
  }
  else if (type == VARIABLESYNONYM) {
    return VARN;
  }
  else if (type == PROCEDURESYNONYM) {
    return PROCEDUREN;
  }
  else if (type == STMTSYNONYM) {
    return STMTN;
  }
  else if (type == PROGLINESYNONYM) {
    return STMTN;
  }
  else if (type == CALLSYNONYM) {
    return CALLN;
  }
  else if (type == IFSYNONYM) {
    return IFN;
  }
}