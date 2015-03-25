#pragma once
#include <vector>
#include <string>
#include <map>
#include "GlobalType.h"

using namespace std;

class QueryResult {
	typedef vector<int> R_TUPLE;
	typedef vector<int> CROSS_INDEX_LIST;
	typedef vector<int> INDEX_LIST;
private:
	int numSynonyms;
	vector<string> synonyms;
	map<string, int> indexMap;

	vector <R_TUPLE> solutions;
	pair<CROSS_INDEX_LIST, CROSS_INDEX_LIST> matchingSynonyms(QueryResult result2);
	R_TUPLE getSubResult(const R_TUPLE&, const INDEX_LIST&);
	const int NO_MATCH = -1;
public:
	QueryResult(vector<string> synonyms);
	~QueryResult();
	void addSolution(R_TUPLE solution);
	string toString(map<string, QNodeType> typeMap);
	QueryResult merge(QueryResult result2);
	map<R_TUPLE, vector<R_TUPLE > > createExtensionMap(INDEX_LIST matchIndex);
}