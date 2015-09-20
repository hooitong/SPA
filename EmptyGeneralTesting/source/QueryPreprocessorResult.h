#pragma once

#include <string>
#include <map>
#include "QNode.h"
#include "QueryPreprocessorDeclaration.h"
#include "QueryAttributeTable.h"
using namespace std;

class QueryPreprocessorResult
{
public:
	QueryPreprocessorResult(QueryPreprocessorDeclaration* declaration);
	~QueryPreprocessorResult(void);
	QNode* getResultTree(string result_string);
	QNode* getResultNode(string result_elem);
	bool isValidResult(void);

private:
	QueryPreprocessorDeclaration* declaration;
	QueryAttributeTable* attribute_table;
	bool isValid;
};

