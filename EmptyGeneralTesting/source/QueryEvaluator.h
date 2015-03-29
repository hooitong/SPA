#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <sstream>

#include "PKB.h"
#include "QueryTree.h"
#include "QueryResult.h"


class QueryEvaluator {
  public:
    string evaluate(QueryTree* tree);

// Handle evaluation with wildcards of a certain type. (May be relocated in the future)
  private:
    PKB pkbInstance; //Stub instance for coding. Need to have instance accessible by Query System.
	QueryResult evaluate(QNode* node);
    vector<std::pair<STMTLINE, STMTLINE>> Follows(TType firstType, TType secondType);
    vector<std::pair<STMTLINE, STMTLINE>> Parent(TType firstType, TType secondType);
    vector<std::pair<STMTLINE, VARINDEX>> Modifies(TType firstType); // get all tuples of the type + var that it modifies
    vector<std::pair<STMTLINE, VARINDEX>> Uses(TType firstType); // get all tuples of the type + var that it uses
	TType synonymToTType(QNodeType type);
	int getInteger(QNode* node);
	QueryResult solveRelation(QNode* node);
	QueryResult solveFollows(QNode* node);
	QueryResult solveParent(QNode* node);
	bool isSynonym(QNodeType type);
	QueryResult pairsToResult(vector<pair<int,int> > pairs, string synonym1, string synonym2);
	QueryResult singlesToResult(vector<int> singles, string synonym);
	QueryResult oneToResult(int oneResult, string synonym);
	QueryResult boolToResult(bool boolResult);
	QueryResult getAllOfType(TType t, string synonym);
};