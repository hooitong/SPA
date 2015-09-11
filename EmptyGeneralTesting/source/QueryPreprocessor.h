#pragma once

#include <string>
#include <map>

#include "QueryTree.h"
#include "QueryPreprocessorDeclaration.h"

class QueryPreprocessor {
  public:
    QueryTree* parseQuery(string query);
    QueryPreprocessor(void);
    ~QueryPreprocessor(void);

    /*--------------------checking -------------------*/
    bool checkAttributeName(string attName);
    static bool isIdent(string ident);
    bool checkInteger(string number);
    bool checkAttReference(string attReference);
    bool checkElem(string elem);
    bool checkVarReference(string varReference);
    static bool isDesignEntityType(string entity);
    bool addTuple(string single_tuple);
    bool checkTuple(string tuple);
	bool checkAttrRef(string attributeReference);
	bool checkAttrName(string attribute);
    bool checkFactor(string factor);

    /*------------------------------------------------*/

    static string trim(string s);

    bool checkConditionExists(string query);
    bool trimAndCheckClause(string clause, int num);
    bool splitAndCheckClause(string clause, int num);
    bool checkAttribute(string attribute);
    bool checkPattern(string pattern);
    bool checkRelation(string relation);
    bool checkWhile(string pattern);
    bool checkIf(string pattern);
    bool checkAssign(string pattern, string patternName);
    bool checkDeclaration(string declaration);
    bool checkExpression(string expression);
    int findIndexOfType(string type);
    QNode* parseStmtRef(string argument);
    QNode* parseVarRef(string argument);
    QNode* parseEntRef(string argument);
	QNode* parseEntRefNoUnderscore(string argument);

  private:
    map<int, int> posOfConds;

    map<int, int> posOfConds1;
    int table[5][24];
    QueryTree *queryTree;
    QNode *resultListNode;
	QNode *conditionsNode;
	QueryPreprocessorDeclaration* declaration;

};