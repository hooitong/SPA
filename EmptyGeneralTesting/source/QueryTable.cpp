#include "QueryTable.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;



QueryTable::QueryTable(void) {

	fillNodeAttrTypeTable();
    string array1[] = { "prog_line","stmt", "if", "while","call","assign", "procedure", "variable"};
    string array2[] = { "prog_line","stmt","assign"};

	vector<string> procNameList;
    procNameList.push_back("call");
    procNameList.push_back("procedure");
    attribute procNameEntry ={procNameList,"string"};
    attributeTable["procName"] =procNameEntry;

    vector<string> varNameList;
    varNameList.push_back("variable");
    attribute varNameEntry = {varNameList,"string"};
    attributeTable["varName"] = varNameEntry;

    vector<string> valueList;
    valueList.push_back("constant");
    attribute valueEntry= {valueList,"integer"};
    attributeTable["value"] = valueEntry;

    vector<string> stmtList;
    stmtList.push_back("call");
    stmtList.push_back("assign");
    stmtList.push_back("if");
    stmtList.push_back("while");
    stmtList.push_back("stmt");
    attribute stmtEntry = {stmtList,"integer"};
    attributeTable["stmt#"] = stmtEntry;

    vector<string> progLineList;
    progLineList.push_back("prog_line");
    attribute progLineEntry = {progLineList,"integer"};
    attributeTable["prog_line"] = progLineEntry;

}

string QueryTable::getAttribute(QueryPreprocessorDeclaration* declaration,string prefix, string postfix){

	attribute e = attributeTable[postfix];
	string reference_type = declaration->getSynonymType(prefix);
	for(unsigned int i = 0; i < e.prefix_type.size() ; i++){
		if(reference_type == e.prefix_type[i]){
			//cout <<"e.intOrStrType :" << e.intOrStrType << endl;
            return e.intOrStrType;
			break;
		}
	}
	return "false";

}
void QueryTable::fillNodeAttrTypeTable(){
	string_attrtype_to_node_type["procName"] = VAR;
    string_attrtype_to_node_type["varName"] = VAR;
    string_attrtype_to_node_type["value"] = CONST;
	string_attrtype_to_node_type["stmt#"] = CONST;
}

QNode* QueryTable::getAttrTypeNode(string attribute) {

	if (string_attrtype_to_node_type.count(attribute) == 0) {
		return NULL;
	}
	QNodeType node_type = string_attrtype_to_node_type[attribute];
	//cout <<node_type << "," <<attribute <<endl;
	return new QNode(node_type, attribute);
}