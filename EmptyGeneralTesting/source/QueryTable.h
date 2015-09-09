#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;


class QueryTable {
  public:
	QueryTable(void);
    struct entity {
        string type;
        string synonym;
    };

	struct attribute{ // for attr_compare table
        vector<string> prefix_type;
        string intOrStrType;
    };

	void addEntry(string condition, string array1[], string array2[], int len1,  int len2, int len3, int len4 );
	void addParentTEntry();
	//map<string,attr_entry> attr_table;
	struct arg_type_list{
		vector<string> synonym_type;
	};
	struct entry{ // for table driven type checking
		arg_type_list arg1_list;
		arg_type_list arg2_list;
	};
	map<string,entry> table;
	map<string,attribute> attributeTable;

};
