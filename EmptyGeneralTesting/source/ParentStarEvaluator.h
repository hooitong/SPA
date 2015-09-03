#pragma once

#include <PKB.h>
#include <QueryResult.h>
#include <QNode.h>
#include <RelationEvaluator.h>

class ParentStarEvaluator : RelationEvaluator
{
  public:
    QueryResult evaluate(QNode* node);
    ParentStarEvaluator(PKB* pkb): RelationEvaluator(pkb) {}
  private:
    QueryResult evaluateSynSyn(QNode* node);
    QueryResult evaluateSynConst(QNode* node);
    QueryResult evaluateSynAny(QNode* node);
    QueryResult evaluateConstSyn(QNode* node);
    QueryResult evaluateConstConst(QNode* node);
    QueryResult evaluateConstAny(QNode* node);
    QueryResult evaluateAnySyn(QNode* node);
    QueryResult evaluateAnyConst(QNode* node);
    QueryResult evaluateAnyAny(QNode* node);
};