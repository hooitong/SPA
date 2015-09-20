#include "AffectsEvaluator.h"

QueryResult AffectsEvaluator::evaluate(QNode* node) {
  QNode* leftChild = node->getChildren()[0];
  QNode* rightChild = node->getChildren()[1];
  if (leftChild->getQType() == ANY &&
    rightChild->getQType() == ANY) {
    return evaluateAnyAny(node);
  }
  else if (leftChild->getQType() == ANY &&
    isSynonym(rightChild->getQType())) {
    return evaluateAnySyn(node);
  }
  else if (leftChild->getQType() == ANY &&
    rightChild->getQType() == CONST) {
    return evaluateAnyConst(node);
  }
  else if (isSynonym(leftChild->getQType()) &&
    rightChild->getQType() == ANY) {
    return evaluateSynAny(node);
  }
  else if (isSynonym(leftChild->getQType()) &&
    isSynonym(rightChild->getQType())) {
    return evaluateSynSyn(node);
  }
  else if (isSynonym(leftChild->getQType()) &&
    rightChild->getQType() == CONST) {
    return evaluateSynConst(node);
  }
  else if (leftChild->getQType() == CONST &&
    rightChild->getQType() == ANY) {
    return evaluateConstAny(node);
  }
  else if (leftChild->getQType() == CONST &&
    isSynonym(rightChild->getQType())) {
    return evaluateConstSyn(node);
  }
  else if (leftChild->getQType() == CONST &&
    rightChild->getQType() == CONST) {
    return evaluateConstConst(node);
  }
}

QueryResult AffectsEvaluator::evaluateAnyAny(QNode* node) {
  Modifies *modifies = pkb->getModifies();
  Uses *uses = pkb->getUses();
  vector<STMTLINE> leftLines = pkb->getAst()->getStmtLines(TType::STMTN);

}

QueryResult AffectsEvaluator::evaluateAnyConst(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateAnySyn(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateConstAny(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateConstConst(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateConstSyn(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateSynAny(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateSynConst(QNode* node) {

}

QueryResult AffectsEvaluator::evaluateSynSyn(QNode* node) {

}