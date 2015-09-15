#pragma once

#include <string>
#include <map>

#include "QueryTree.h"
#include "QueryPreprocessorDeclaration.h"
#include "QueryPreprocessorResult.h"
#include "QueryPreprocessorCondition.h"

class QueryPreprocessor {
  public:
    QueryTree* parseQuery(string query);
    QueryPreprocessor(void);
    ~QueryPreprocessor(void);

    /*--------------------checking -------------------*/
    static bool isAttributeName(string attName);
    static bool isIdent(string ident);
    static bool checkInteger(string number);
    static bool isAttReference(string attReference);
    static bool isElem(string elem);
    bool checkVarReference(string varReference);
    static bool isDesignEntityType(string entity);
    bool addTuple(string single_tuple);
    bool checkTuple(string tuple);
	bool checkAttrRef(string attributeReference);
	bool checkAttrName(string attribute);
    bool checkFactor(string factor);

    /*------------------------------------------------*/

    static string trim(string s);
	static int find(string long_string, string substring_to_find, int start_search_index);
	static int find(string long_string, string substring_to_find);

    bool checkAttribute(string attribute);
    bool checkPattern(string pattern);
    bool checkWhile(string pattern);
    bool checkIf(string pattern);
    bool checkAssign(string pattern, string patternName);
    bool checkDeclaration(string declaration);
    bool checkExpression(string expression);
    int findIndexOfType(string type);

  private:
	int getFirstConditionIndex(string query, int start_index);
    map<int, int> posOfConds;

    map<int, int> posOfConds1;
    QueryTree *queryTree;
    QNode *resultListNode;
	QNode *conditionListNode;
	QueryPreprocessorDeclaration* declaration;
	QueryPreprocessorResult* result;
	QueryPreprocessorCondition* condition;
};