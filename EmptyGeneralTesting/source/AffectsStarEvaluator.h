#pragma once

#include "PKB.h"
#include "QueryResult.h"
#include "QNode.h"

class AffectsStarEvaluator {
public:
    AffectsStarEvaluator(PKB* pkb);
    QueryResult evaluate(QNode* node);
private:
    PKB* pkb;
    QueryResult solveAnyAny(QNode* node);
    QueryResult solveAnyConst(QNode* node);
    QueryResult solveAnySyn(QNode* node);
    QueryResult solveConstAny(QNode* node);
    QueryResult solveConstConst(QNode* node);
    QueryResult solveConstSyn(QNode* node);
    QueryResult solveSynAny(QNode* node);
    QueryResult solveSynConst(QNode* node);
    QueryResult solveSynSyn(QNode* node);
    bool affectsFromStmtToAny(STMTLINE stmt);
    bool affectsFromAnyToStmt(STMTLINE stmt);
    set<int> affectsFromStmtToSyn(STMTLINE stmt);
    set<int> affectsFromSynToStmt(STMTLINE stmt);
    bool isSynonym(QNodeType type);
    bool isConst(QNodeType type);
};