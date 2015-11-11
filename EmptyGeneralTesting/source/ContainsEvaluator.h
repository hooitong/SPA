#pragma once

#include "PKB.h"
#include "QueryResult.h"
#include "QNode.h"

class ContainsEvaluator {
public:
    ContainsEvaluator(PKB* pkb);
    QueryResult evaluate(QNode* node);
private:
    PKB* pkb;
    QueryResult solveConstConst(QNode* node);
    QueryResult solveConstSyn(QNode* node);
    QueryResult solveSynConst(QNode* node);
    QueryResult solveSynSyn(QNode* node);
    void getAllTNodesFrom(TNode* node, vector<TNode*> &result);
    vector<TNode*> getTNodes(QNode* node);
    int toInt(TNode* node);
    TType toTType(QNodeType type);
    bool matchType(QNodeType qtype, TType ttype);
};