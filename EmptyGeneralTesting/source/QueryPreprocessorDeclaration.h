#pragma once

#include <string>
#include <map>
#include "QNode.h"
using namespace std;

class QueryPreprocessorDeclaration
{
public:
	QueryPreprocessorDeclaration(string declaration_string);
	~QueryPreprocessorDeclaration(void);
	bool isValidDeclaration(void);
	bool isDeclaredSynonym(string synonym);
	string getSynonymType(string synonym);
	QNode* getSynonymTypeNode(string synonym);

private:
	void processDeclarationClause(string declaration_clause);
	void declareSynonym(string synonym_type, string synonym_name);
	bool isValid;
	void fillNodeTypeTable(void);
	map<string, string> synonym_to_type;
	map<string, QNodeType> string_type_to_node_type;
};

