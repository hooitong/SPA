#pragma once

#include <QNode.h>
#include <QueryResult.h>
#include <PKB.h>

class RelationEvaluator
{
  protected:
    PKB* pkb;
  protected:
    int getInteger(QNode* node);
    TType synonymToTType(QNodeType type);
    bool isSynonym(QNodeType type);
    vector<STMTLINE> filter(vector<STMTLINE> original, TType type);
  public:
    RelationEvaluator(PKB* pkb);
    virtual QueryResult evaluate(QNode* node) = 0;
};