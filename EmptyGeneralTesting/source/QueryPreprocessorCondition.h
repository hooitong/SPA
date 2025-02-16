#pragma once

#include <string>
#include <map>
#include "QNode.h"
#include "QueryPreprocessorDeclaration.h"
#include "QueryRelationTable.h"
#include "QueryAttributeTable.h"
#include "QueryTable.h"
using namespace std;

class QueryPreprocessorCondition
{
public:
	QueryPreprocessorCondition(QueryPreprocessorDeclaration* declaration);
	~QueryPreprocessorCondition(void);
	QNode* getConditionTree(string condition_string);
	bool isValidCondition(void);

private:
	QueryRelationTable* relation_table;
	QueryAttributeTable* attribute_table;
	QueryTable* query_table;
	QNode* condition_root;
	QueryPreprocessorDeclaration* declaration;
	bool is_valid;
	void processConditions(string conditions_string);
	void processSuchThat(string such_that_string);
	void processWith(string with_string);
	pair<QNode*, RefType> processWithReference(string reference_string);
	void processPattern(string pattern_string, bool allow_extension);
	bool isValidExpression(string expression);
	string removeExpressionQuote(string expression);
	QNode* parseRef(string argument);
};

