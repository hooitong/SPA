#pragma once

#include "QNode.h"
#include "QueryResult.h"
#include "PKB.h"

class RelationEvaluator
{
  protected:
    PKB* pkb;
  private:
    virtual bool solveConstConst(const int left, const int right, const QueryResult& result) const = 0;
    virtual vector<int> solveConstSyn(const int left, const QueryResult& result) const = 0;
    virtual vector<int> solveSynConst(const int right, const QueryResult& result) const = 0;
    virtual int getConstLeft(const QNode* const node) const = 0;
    virtual int getConstRight(const QNode* const node) const = 0;
    virtual vector<int> getAllLeft(const QNode* const node, 
        const QueryResult &result) const = 0;
    virtual vector<int> getAllRight(const QNode* const node, 
        const QueryResult &result) const = 0;
    virtual bool checkRight(const QNode* const node,
        const int tested) const = 0;
    virtual bool checkLeft(const QNode* const node,
        const int tested) const = 0;
  protected:
    int getInteger(QNode* node) const;
    TType synonymToTType(QNodeType type) const;
    bool isSynonym(QNodeType type) const;
    bool isConst(QNodeType type) const;
    vector<STMTLINE> filter(vector<STMTLINE> original, TType type) const;
    void updateAnyAny(const QNode* const node, QueryResult& result) const;
    void updateAnyConst(const QNode* const node, QueryResult& result) const;
    void updateAnySyn(const QNode* const node, QueryResult& result) const;
    void updateConstAny(const QNode* const node, QueryResult& result) const;
    void updateConstConst(const QNode* const node, QueryResult& result) const;
    void updateConstSyn(const QNode* const node, QueryResult& result) const;
    void updateSynAny(const QNode* const node, QueryResult &result) const;
    void updateSynConst(const QNode* const node, QueryResult &result) const;
    void updateSynSyn(const QNode* const node, QueryResult &result) const;

  public:
    RelationEvaluator(PKB* pkb);
    virtual QueryResult evaluate(QNode* node);
    void updateResult(const QNode* const &node, QueryResult& result);

};