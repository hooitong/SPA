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
  return QueryResult(false);
}

QueryResult AffectsEvaluator::evaluateAnyConst(QNode* node) {
    
  return QueryResult(false);
}

QueryResult AffectsEvaluator::evaluateAnySyn(QNode* node) {
    
  return QueryResult(false);
}

QueryResult AffectsEvaluator::evaluateConstAny(QNode* node) {
  return QueryResult(false);

}

QueryResult AffectsEvaluator::evaluateConstConst(QNode* node) {
  return QueryResult(false);

}

QueryResult AffectsEvaluator::evaluateConstSyn(QNode* node) {
    
  return QueryResult(false);
}

QueryResult AffectsEvaluator::evaluateSynAny(QNode* node) {
  return QueryResult(false);

}

QueryResult AffectsEvaluator::evaluateSynConst(QNode* node) {
  return QueryResult(false);

}

QueryResult AffectsEvaluator::evaluateSynSyn(QNode* node) {
  return QueryResult(false);

}