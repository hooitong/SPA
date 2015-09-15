#pragma once

#include <PKB.h>
#include <QueryResult.h>
#include <QNode.h>
#include <RelationEvaluator.h>

class UsesEvaluator : RelationEvaluator
{
  public:
    QueryResult evaluate(QNode* node);
    UsesEvaluator(PKB* pkb): RelationEvaluator(pkb) {}
  private:
    QueryResult evaluateSynSyn(QNode* node);
    QueryResult evaluateSynConst(QNode* node);
    QueryResult evaluateSynAny(QNode* node);
    QueryResult evaluateConstSyn(QNode* node);
    QueryResult evaluateConstConst(QNode* node);
    QueryResult evaluateConstAny(QNode* node);
    QueryResult evaluateProcsynSyn(QNode* node);
    QueryResult evaluateProcsynConst(QNode* node);
    QueryResult evaluateProcsynAny(QNode* node);
    QueryResult evaluateProcSyn(QNode* node);
    QueryResult evaluateProcConst(QNode* node);
    QueryResult evaluateProcAny(QNode* node);
};