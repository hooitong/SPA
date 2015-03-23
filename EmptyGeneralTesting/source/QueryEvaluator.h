#pragma once
#include "QueryTree.h"
#include <string>

using namespace std;

class QueryEvaluator {
public:
	string evaluate(QueryTree* tree);
};