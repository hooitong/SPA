#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>

#include "GlobalType.h"

class QueryResult {
    typedef vector<int> R_TUPLE;
    typedef vector<int> CROSS_INDEX_LIST;
    typedef vector<int> INDEX_LIST;
  private:
    int numSynonyms;
    vector<string> synonyms;
    map<string, int> indexMap;
    map<string, set<int> > possibleValues;

    vector <R_TUPLE> solutions;
    pair<CROSS_INDEX_LIST, CROSS_INDEX_LIST> matchingSynonyms(QueryResult result2);
    R_TUPLE getSubResult(const R_TUPLE&, const INDEX_LIST&);
    map<R_TUPLE, vector<R_TUPLE > > createExtensionMap(INDEX_LIST matchIndex);
    static const int NO_MATCH = -1;
  public:
    QueryResult(bool possible);
    QueryResult(int result, string synonym);
    QueryResult(vector<int> results, string synonym);
    QueryResult(vector<pair<int, int> > results, string synonym1, string synonym2);
    QueryResult(vector<string> synonyms);
    ~QueryResult();
    vector<string> getSynonyms();
    int getIndex(string synonym);
    void addSolution(R_TUPLE solution);
    QueryResult merge(QueryResult result2);
    QueryResult filter(vector<string> synonyms);
    void append(QueryResult result2);
    bool operator==(QueryResult result2);
    set<int> getPossibleValues(string synonym) const;
    int getSolutionsSize();
    int getSolutionForSynonym(int solutionIndex, string synonym);
    vector<R_TUPLE> getResult();
};