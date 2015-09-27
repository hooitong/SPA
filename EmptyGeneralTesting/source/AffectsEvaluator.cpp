#include "AffectsEvaluator.h"
#include <algorithm>

/*
  TODO: Code is currently unoptimized and untested. Does not use result to compute as well.
*/

AffectsEvaluator::AffectsEvaluator(PKB* pkb) : RelationEvaluator(pkb) {}

bool AffectsEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const {
  AST *ast = pkb->getAst();

  /* Left and Right are Statement Lines */
  /* Check that both statement lines are assignment statements */
  bool isTypeCorrect = ast->getTNode(left)->getTType() == ASSIGNN && ast->getTNode(right)->getTType() == ASSIGNN;

  /* Check that both are modifying and using the same variable and save variable */
  /* TODO: Will crash if the statement does not modifies or uses */
  VARINDEX contextVar = pkb->getModifies()->getModifiedByStmt(left)[0];
  bool isSameContext = pkb->getUses()->getUsedByStmt(right)[0];

  /* Check that there is a control path from left to right */
  bool isContainsPath = pkb->getNext()->isNextStar(left, right);

  /* Heavy computation alert! Using Next table, check the statement lines whether other variable modifies it */
  vector<STMTLINE> path;
  bool isNotModifiedBetween = findPathToNode(left, right, contextVar, path);

  /* If all boolean is true then return true else false */
  return isTypeCorrect && isSameContext && isContainsPath && isNotModifiedBetween;
}

vector<int> AffectsEvaluator::solveConstSyn(const int left, const QueryResult& result) const {
  /* Retrieve all statements reached by left */
  vector<STMTLINE> possibleRight = pkb->getNext()->getNextStar(left);

  /* TODO: Lazy implementation by computing one by one */
  vector<STMTLINE> resultRight;
  for (int i = 0; i < possibleRight.size(); i++) {
    /* Only applies to assignment statements */
    if (pkb->getAst()->getTNode(possibleRight[i])->getTType() == ASSIGNN) {
      if (solveConstConst(left, possibleRight[i], result)) resultRight.push_back(possibleRight[i]);
    }
  }

  return resultRight;
}

vector<int> AffectsEvaluator::solveSynConst(const int right, const QueryResult& result) const {
  /* Retrieve all statements that can reach to right */
  vector<STMTLINE> possibleLeft = pkb->getNext()->getBeforeStar(right);

  /* TODO: Lazy implementation by computing one by one */
  vector<STMTLINE> resultLeft;
  for (int i = 0; i < possibleLeft.size(); i++) {
    /* Only applies to assignment statements */
    if (pkb->getAst()->getTNode(possibleLeft[i])->getTType() == ASSIGNN) {
      if (solveConstConst(right, possibleLeft[i], result)) resultLeft.push_back(possibleLeft[i]);
    }
  }

  return resultLeft;
}

int AffectsEvaluator::getConstLeft(const QNode* const node) const {
  return true;
}

int AffectsEvaluator::getConstRight(const QNode* const node) const {
  return true;
}

bool AffectsEvaluator::checkLeft(const QNode* const node, const int tested) const {
  return true;
}

bool AffectsEvaluator::checkRight(const QNode* const node, const int tested) const {
  return true;
}

vector<int> AffectsEvaluator::getAllLeft(const QNode* const node, const QueryResult& result) const {
  vector<int> temp;
  return temp;
}

vector<int> AffectsEvaluator::getAllRight(const QNode* const node, const QueryResult& result) const {
  vector<int> temp;
  return temp;
}

bool AffectsEvaluator::findPathToNode(STMTLINE current, STMTLINE end, VARINDEX contextVar, vector<STMTLINE> path) const {
  /* Base Case */
  if (current == end) return true;

  /* Early terminate if this stmtline cannot reach end path */
  if (!pkb->getNext()->isNextStar(current, end)) return false;

  /* Check cyclic in path */
  if (std::find(path.begin(), path.end(), current) != path.end()) return false;

  /* Check current stmtline whether it modifies variable */
  if (path.size() != 0 && current != end && pkb->getModifies()->isModifiesForStmt(current, contextVar)) return false;

  /* Get all possible next path and navigate recursively */
  vector<STMTLINE> allNext = pkb->getNext()->getNext(current);
  bool pathsStatus = false;
  path.push_back(current);
  for (int i = 0; i < allNext.size(); i++) {
    pathsStatus = pathsStatus | findPathToNode(allNext[i], end, contextVar, path);
  }

  return pathsStatus;
}
