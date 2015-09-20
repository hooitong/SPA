#pragma once

#include "QueryPreprocessorDeclaration.h"
#include <string>
#include <map>
#include <vector>
using namespace std;


class QueryTable {
  public:
	QueryTable(void);
	/*
    struct entity {
        string type;
        string synonym;
    };
	*/
	struct attribute{ // for attr_compare table
        vector<string> prefix_type;
        string intOrStrType;
    };
	string getAttribute(QueryPreprocessorDeclaration* declaration, string prefix, string postfix);
	void fillNodeAttrTypeTable();
	QNode* getAttrTypeNode(string attribute);


	QueryPreprocessorDeclaration* declaration;
	map<string,attribute> attributeTable;
	map<string, QNodeType> string_attrtype_to_node_type;

};