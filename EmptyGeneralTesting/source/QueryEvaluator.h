#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <list>

#include "PKB.h"
#include "QueryTree.h"
#include "QueryResult.h"

class QueryEvaluator {
  public:
    QueryEvaluator(PKB* pkb);
    std::list<string> evaluate(QueryTree* tree);

// Handle evaluation with wildcards of a certain type. (May be relocated in the future)
  private:
    PKB* pkbInstance; //Stub instance for coding. Need to have instance accessible by Query System.
    QueryResult evaluate(QNode* node);
    vector<STMTLINE> filter(vector<STMTLINE> original, TType type);
    TType synonymToTType(QNodeType type);
    int getInteger(QNode* node);
    QueryResult solveRelation(QNode* node);
    QueryResult solveFollows(QNode* node);
    QueryResult solveFollowsStar(QNode* node);
    QueryResult solveParent(QNode* node);
    QueryResult solveParentStar(QNode* node);
    QueryResult solveModifies(QNode* node);
    QueryResult solveModifiesProc(QNode* node);
    QueryResult solveUses(QNode* node);
    QueryResult solveUsesProc(QNode* node);
    QueryResult solvePattern(QNode* node);
    QueryResult solveCalls(QNode* node);
    QueryResult solveCallsStar(QNode* node);
    QueryResult solveWith(QNode* node);
    QueryResult solveNext(QNode* node);
    QueryResult solveNextStar(QNode* node);
    QueryResult solveAffects(QNode* node);
    QueryResult solveAffectsStar(QNode* node);
    QueryResult solveAffectsBip(QNode* node);
    QueryResult solvePatternIf(QNode* node);
    QueryResult solvePatternWhile(QNode* node);
    QueryResult solveAffectsBipStar(QNode* node);
    QueryResult solveNextBip(QNode* node);
    QueryResult solveNextBipStar(QNode* node);
    QueryResult solveContains(QNode* node);
    QueryResult solveContainsStar(QNode* node);
    QueryResult solveSibling(QNode* node);
    bool isSynonym(QNodeType type);
    vector<QueryResult> getResultFilters(QNode* node, QueryResult& result);
    vector<string> getResultSynonyms(QNode* node);
    map<string, TType> getSynonymMap(QNode* node);
};