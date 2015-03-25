#pragma once

#include "QueryTree.h"

#include <string>


class QueryEvaluator {
public:
	string evaluate(QueryTree* tree);

// Handle evaluation with wildcards of a certain type. (May be relocated in the future)
private:
	vector<std::pair<STMTLINE, STMTLINE>> Follows(TType firstType, TType secondType);
	vector<std::pair<STMTLINE, STMTLINE>> Parent(TType firstType, TType secondType);
	vector<std::pair<STMTLINE, STMTLINE>> Modifies(TType firstType, TType secondType);
	vector<std::pair<STMTLINE, STMTLINE>> Uses(TType firstType, TType secondType);
};