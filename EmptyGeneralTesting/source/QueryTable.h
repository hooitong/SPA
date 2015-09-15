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
	/*
	void addEntry(string condition, string array1[], string array2[], int len1,  int len2, int len3, int len4 );
	
	struct arg_type_list{
		vector<string> synonym_type;
	};
	struct entry{ // for table driven type checking
		arg_type_list arg1_list;
		arg_type_list arg2_list;
	};
	map<string,entry> table;
	*/

	QueryPreprocessorDeclaration* declaration;
	map<string,attribute> attributeTable;
	map<string, QNodeType> string_attrtype_to_node_type;

};
