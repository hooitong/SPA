#pragma once

#include "PKB.h"
#include "QueryResult.h"
#include "QNode.h"
#include "RelationEvaluator.h"

class CallsEvaluator : public RelationEvaluator
{
  public:
    CallsEvaluator(PKB* pkb);
  private:
    bool solveConstConst(const int left, const int right, const QueryResult& result) const;
    vector<int> solveConstSyn(const int left, const QueryResult& result) const;
    vector<int> solveSynConst(const int right, const QueryResult& result) const;
    int getConstLeft(const QNode* const node) const;
    int getConstRight(const QNode* const node) const;
    vector<int> getAllLeft(const QNode* const node, 
        const QueryResult &result) const;
    vector<int> getAllRight(const QNode* const node, 
        const QueryResult &result) const;
    bool checkRight(const QNode* const node,
        const int tested) const;
    bool checkLeft(const QNode* const node,
        const int tested) const;
};