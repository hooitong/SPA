#pragma once

#include <string>
#include <map>
#include "QNode.h"
#include "QueryPreprocessorDeclaration.h"
using namespace std;

class QueryPreprocessorResult
{
public:
	QueryPreprocessorResult(QueryPreprocessorDeclaration* declaration);
	~QueryPreprocessorResult(void);
	QNode* getResultTree(string result_string);
	QNode* getResultNode(string synonym_name);
	bool isValidResult(void);

private:
	QueryPreprocessorDeclaration* declaration;
	bool isValid;
};

