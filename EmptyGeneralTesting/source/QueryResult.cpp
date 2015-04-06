#include "QueryResult.h"
#include <cassert>
#include <algorithm>

using namespace std;

QueryResult::QueryResult(bool possible) {
	this->numSynonyms = 0;
	this->synonyms = vector<string>();
	this->solutions.clear();
	if (possible) {
		solutions.push_back(R_TUPLE());
	}
}

QueryResult::QueryResult(int result, string synonym) {
	this->numSynonyms = 1;
	this->synonyms.clear();
	this->synonyms.push_back(synonym);
	
	R_TUPLE tuple;
	tuple.push_back(result);
	this->addSolution(tuple);
}

vector<QueryResult::R_TUPLE> QueryResult::getResult() {
	return solutions;
}

QueryResult::QueryResult(vector<int> results, string synonym) {
	this->numSynonyms = 1;
	this->synonyms.clear();
	this->synonyms.push_back(synonym);

	for (int i = 0; i < (int)results.size(); i++) {
		R_TUPLE tuple;
		tuple.push_back(results[i]);
		this->addSolution(tuple);
	}
}

QueryResult::QueryResult(vector<pair<int, int> > results, string synonym1, string synonym2) {
	this->numSynonyms = 2;
	this->synonyms.clear();
	this->synonyms.push_back(synonym1);
	this->synonyms.push_back(synonym2);

	for (int i = 0; i < (int)results.size(); i++) {
		R_TUPLE tuple;
		tuple.push_back(results[i].first);
		tuple.push_back(results[i].second);
		this->addSolution(tuple);
	}
}

void QueryResult::append(QueryResult result2) {
	vector <R_TUPLE> newSolutions = result2.getResult();

	if (solutions.size() == 0) {
		this->numSynonyms = result2.numSynonyms;
		this->synonyms = result2.synonyms;
		this->solutions = result2.solutions;
		return;
	}
	if (newSolutions.size() == 0) {
		return;
	}
	
	assert (synonyms == result2.getSynonyms());
	
	for (int i = 0; i < (int) newSolutions.size(); i++) {
		solutions.push_back(newSolutions[i]);
	}
	sort(solutions.begin(), solutions.end());
	solutions.erase(unique(solutions.begin(), solutions.end()), solutions.end());
}

QueryResult::QueryResult(vector<string> synonyms) {
	this->synonyms = synonyms;
	numSynonyms = synonyms.size();
	for (int i = 0; i < numSynonyms; i++) {
		assert(indexMap.find(synonyms[i]) == indexMap.end());
		indexMap[synonyms[i]] = i;
	}
	solutions.clear();
}

QueryResult::~QueryResult() {
}

void QueryResult::addSolution(vector <int> solution) {
	assert(solution.size() == numSynonyms);
	solutions.push_back(solution);
}

int QueryResult::getIndex(string synonym) {
	if (indexMap.find(synonym) == indexMap.end()) {
		return -1;
	} else {
		return indexMap[synonym];
	}
}

bool QueryResult::operator==(QueryResult result2) {
	if (numSynonyms != result2.numSynonyms) {
		return false;
	}

	pair<CROSS_INDEX_LIST, CROSS_INDEX_LIST> crossIndex = matchingSynonyms(result2);
	for (int i = 0; i < numSynonyms; i++) {
		if (crossIndex.first[i] == -1) {
			return false;
		}
		if (crossIndex.second[i] == -1) {
			return false;
		}
	}

	vector <R_TUPLE> reorderedSolutions1;
	for (int i = 0; i < (int) solutions.size(); i++) {
		reorderedSolutions1.push_back(solutions[i]);
	}
	vector <R_TUPLE> reorderedSolutions2;
	for (int i = 0; i < (int) result2.solutions.size(); i++) {
		reorderedSolutions2.push_back(
			getSubResult(result2.solutions[i], crossIndex.first));
	}

	sort(reorderedSolutions1.begin(), reorderedSolutions1.end());
	sort(reorderedSolutions2.begin(), reorderedSolutions2.end());

	return reorderedSolutions1 == reorderedSolutions2;
}

//TODO: Implement this
string toString(map <string, QNodeType> mp) {
	return "";
}

pair<QueryResult::CROSS_INDEX_LIST, QueryResult::CROSS_INDEX_LIST > 
	QueryResult::matchingSynonyms(QueryResult result2) {

	vector <int> matchThis;
	vector <int> matchResult2;
	for (int i = 0; i < numSynonyms; i++) {
		if (result2.indexMap.find(synonyms[i]) == result2.indexMap.end()) {
			matchThis.push_back(NO_MATCH);
		} else {
			matchThis.push_back(result2.indexMap[synonyms[i]]);
		}
	}

	for (int i = 0; i < result2.numSynonyms; i++) {
		if (indexMap.find(result2.synonyms[i]) == indexMap.end()) {
			matchResult2.push_back(NO_MATCH);
		} else {
			matchResult2.push_back(indexMap[result2.synonyms[i]]);
		}
	}
	return make_pair(matchThis, matchResult2);;
}

QueryResult::R_TUPLE QueryResult::getSubResult (const QueryResult::R_TUPLE &tuple, 
	const QueryResult::INDEX_LIST &indexes) {

	R_TUPLE subResult;
	for (int i = 0; i < (int) indexes.size(); i++) {
		subResult.push_back(tuple[indexes[i]]);
	}
	return subResult;
}

vector<string> QueryResult::getSynonyms() {
	return synonyms;
}

QueryResult QueryResult::filter(vector<string> newSynonyms) {
	QueryResult newResult(newSynonyms);
	pair<vector<int>, vector<int> > matchingIndex = matchingSynonyms(newResult);

	INDEX_LIST matchingInThis;
	for (int i = 0; i < (int)newSynonyms.size(); i++) {
		if (matchingIndex.second[i] != -1) {
			matchingInThis.push_back(matchingIndex.second[i]);
		}
	}

	for (int i = 0; i < (int) solutions.size(); i++) {
		R_TUPLE subResult = getSubResult(solutions[i], matchingInThis);
		newResult.addSolution(subResult);
	}
	sort(newResult.solutions.begin(), newResult.solutions.end());
	newResult.solutions.erase(unique(newResult.solutions.begin(),
		newResult.solutions.end()),
		newResult.solutions.end());

	return newResult;
}

QueryResult QueryResult::merge(QueryResult result2) {
	pair<vector<int>, vector<int> > matchingIndex = matchingSynonyms(result2);

	vector <string> newSynonyms;
	for (int i = 0; i < numSynonyms; i++) {
		newSynonyms.push_back(synonyms[i]);
	}

	for (int i = 0; i < result2.numSynonyms; i++) {
		if (matchingIndex.second[i] == NO_MATCH) {
			newSynonyms.push_back(result2.synonyms[i]);
		}
	}

	INDEX_LIST matchingInThis;
	for (int i = 0; i < result2.numSynonyms; i++) {
		if (matchingIndex.second[i] != -1) {
			matchingInThis.push_back(matchingIndex.second[i]);
		}
	}

	map<R_TUPLE, vector<R_TUPLE> > extensionMap = result2.createExtensionMap(matchingIndex.second);
	QueryResult newResult = QueryResult(newSynonyms);

	for (int i = 0; i < (int) solutions.size(); i++) {
		R_TUPLE matchingSubResult = getSubResult(solutions[i], matchingInThis);
		if (extensionMap.find(matchingSubResult) != extensionMap.end()) {
			for (int j = 0; j < (int)extensionMap[matchingSubResult].size(); j++) {
				R_TUPLE newTuple = solutions[i];
				for (int k = 0; k < (int)extensionMap[matchingSubResult][j].size(); k++) {
					newTuple.push_back(extensionMap[matchingSubResult][j][k]);
				}
				newResult.addSolution(newTuple);
			}
		}
	}

	return newResult;

}

map<QueryResult::R_TUPLE, vector<QueryResult::R_TUPLE> > 
	QueryResult::createExtensionMap(CROSS_INDEX_LIST matchingIndex) {

	INDEX_LIST matchIndexes;
	INDEX_LIST noMatchIndexes;
	for (int i = 0; i < numSynonyms; i++) {
		if (matchingIndex[i] == NO_MATCH) {
			noMatchIndexes.push_back(i);
		} else {
			matchIndexes.push_back(i);
		}
	}

	map <vector<int>, vector<vector<int> > > extensionMap;

	for (int i = 0; i < (int) solutions.size(); i++) {
		vector <int> subResultMatch = getSubResult(solutions[i], matchIndexes);
		vector <int> subResultNoMatch = getSubResult(solutions[i], noMatchIndexes);
		if (extensionMap.find(subResultMatch) == extensionMap.end()) {
			extensionMap[subResultMatch] = vector<vector<int> >();
		}
		extensionMap[subResultMatch].push_back(subResultNoMatch);
	}
	return extensionMap;
}