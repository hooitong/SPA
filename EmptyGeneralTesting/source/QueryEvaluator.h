#pragma once
#include "QueryTree.h"
#include <string>
#include <set>

using namespace std;

class QueryEvaluator {
public:
	string evaluate(QueryTree* tree);
};