#include "QueryRelationTable.h"
#include "GlobalType.h"

QueryRelationTable::QueryRelationTable(void) {

	QNodeType modifies_left[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, PROCEDURESYNONYM, CONST, PROC};
	QNodeType modifies_right[] = {VARIABLESYNONYM, VAR, ANY};
	QNodeType uses_left[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, PROCEDURESYNONYM, CONST, PROC};
	QNodeType uses_right[] = {VARIABLESYNONYM, VAR, ANY};
	QNodeType calls_left[] = {PROCEDURESYNONYM, PROC};
	QNodeType calls_right[] = {PROCEDURESYNONYM, PROC};
	QNodeType parent_left[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CONST};
	QNodeType parent_right[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, CONST};
	QNodeType follows_left[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, CONST};
	QNodeType follows_right[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, CONST};
	QNodeType next_left[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, CONST};
	QNodeType next_right[] = {PROGLINESYNONYM, STMTSYNONYM, IFSYNONYM, WHILESYNONYM, CALLSYNONYM, ASSIGNSYNONYM, CONST};
	QNodeType affects_left[] = {PROGLINESYNONYM, STMTSYNONYM, ASSIGNSYNONYM, CONST};
	QNodeType affects_right[] = {PROGLINESYNONYM, STMTSYNONYM, ASSIGNSYNONYM, CONST};

	addRule("Modifies", vector<QNodeType>(modifies_left, modifies_left + 9), vector<QNodeType>(modifies_right, modifies_right + 3));
	addRule("Uses", vector<QNodeType>(uses_left, uses_left + 9), vector<QNodeType>(uses_right, uses_right + 3));
	addRule("Calls", vector<QNodeType>(calls_left, calls_left + 2), vector<QNodeType>(calls_right, calls_right + 2));
	addRule("Calls*", vector<QNodeType>(calls_left, calls_left + 2), vector<QNodeType>(calls_right, calls_right + 2));
	addRule("Parent", vector<QNodeType>(parent_left, parent_left + 5), vector<QNodeType>(parent_right, parent_right + 7));
	addRule("Parent*", vector<QNodeType>(parent_left, parent_left + 5), vector<QNodeType>(parent_right, parent_right + 7));
	addRule("Follows", vector<QNodeType>(follows_left, follows_left + 7), vector<QNodeType>(follows_right, follows_right + 7));
	addRule("Follows*", vector<QNodeType>(follows_left, follows_left + 7), vector<QNodeType>(follows_right, follows_right + 7));
	addRule("Next", vector<QNodeType>(next_left, next_left + 7), vector<QNodeType>(next_right, next_right + 7));
	addRule("Next*", vector<QNodeType>(next_left, next_left + 7), vector<QNodeType>(next_right, next_right + 7));
	addRule("Affects", vector<QNodeType>(affects_left, affects_left + 4), vector<QNodeType>(affects_left, affects_left + 4));
	addRule("Affects*", vector<QNodeType>(affects_left, affects_left + 4), vector<QNodeType>(affects_left, affects_left + 4));

    /*string array1[] = { "prog_line","stmt", "if", "while","call","assign", "procedure", "variable"};
    string array2[] = { "prog_line","stmt","assign"};


    //the first two numbers is the range of the design entity  for arg1_list
    //the last two numbers is the range of the design entity  for arg2_list
    // for this line,  addEntry("Modifies", array1 , array1, 0, 7, 7, 8);
    // 0 7 refers to  "prog_line","stmt", "if", "while","call","assign", "procedure"
    // 7 8 refers to  "variable"
    // the numbers are like index of the array
    addEntry("Modifies", array1 , array1, 0, 7, 7, 8);
    addEntry("Uses", array1 , array1, 0, 7, 7, 8);
    addEntry("Calls", array1 , array1, 6, 7, 6, 7);
    addEntry("Calls*", array1 , array1, 6, 7, 6, 7);
    addEntry("Parent", array1 , array1, 0, 4, 0, 6);
    addEntry("Parent*", array1 , array1, 0, 4, 0, 6);
    addEntry("Follows", array1 , array1, 0, 6, 0, 6);
    addEntry("Follows*", array1 , array1, 0, 6, 0, 6);
    addEntry("Next", array1 , array1, 0, 6, 0, 6);
    addEntry("Next*", array1 , array1, 0, 6, 0, 6);
    addEntry("Affects", array2 , array2, 0, 3, 0, 3);
    addEntry("Affects*", array2 , array2, 0, 3, 0, 3);
	

	vector<string> procNameList;
    procNameList.push_back("call");
    procNameList.push_back("procedure");
    attribute procNameEntry ={procNameList,"string"};
    //attributeTable["procName"] =procNameEntry;

    vector<string> varNameList;
    varNameList.push_back("variable");
    attribute varNameEntry = {varNameList,"string"};
   // attributeTable["varName"] = varNameEntry;

    vector<string> valueList;
    valueList.push_back("constant");
    attribute valueEntry= {valueList,"integer"};
   // attributeTable["value"] = valueEntry;

    vector<string> stmtList;
    stmtList.push_back("call");
    stmtList.push_back("assign");
    stmtList.push_back("if");
    stmtList.push_back("while");
    stmtList.push_back("stmt");
    attribute stmtEntry = {stmtList,"integer"};
   // attributeTable["stmt#"] = stmtEntry;

    vector<string> progLineList;
    progLineList.push_back("prog_line");
    attribute progLineEntry = {progLineList,"integer"};
   // attributeTable["prog_line"] = progLineEntry;
	entry boo = table["Modifies"];
	if (find(boo.arg2_list.synonym_type.begin(), boo.arg2_list.synonym_type.end(),"procedure")!= boo.arg2_list.synonym_type.end() ){
	    cout << "Found" <<endl;
	}else{
	    cout << "Not Found" <<endl;
	} */

}

void QueryRelationTable::addRule(string synonym_name, vector<QNodeType> available_types_left, vector<QNodeType> available_types_right) {
	addRuleLeft(synonym_name, available_types_left);
	addRuleRight(synonym_name, available_types_right);
}

void QueryRelationTable::addRuleLeft(string synonym_name, vector<QNodeType> available_types) {
	if (relation_name_to_available_types.count(synonym_name) == 0) {
		relation_name_to_available_types[synonym_name].first = available_types;
	} else {
		relation_name_to_available_types[synonym_name].first.insert(relation_name_to_available_types[synonym_name].first.begin(), 
			available_types.begin(), available_types.end());
	}
}

void QueryRelationTable::addRuleRight(string synonym_name, vector<QNodeType> available_types) {
	if (relation_name_to_available_types.count(synonym_name) == 0) {
		relation_name_to_available_types[synonym_name].second = available_types;
	} else {
		relation_name_to_available_types[synonym_name].second.insert(relation_name_to_available_types[synonym_name].second.begin(), 
			available_types.begin(), available_types.end());
	}
}

bool QueryRelationTable::isValidRule(string synonym_name, QNodeType left_type, QNodeType right_type) {
	return isValidRuleLeft(synonym_name, left_type) && isValidRuleRight(synonym_name, right_type);
}

bool QueryRelationTable::isValidRuleLeft(string synonym_name, QNodeType type) {
	if (relation_name_to_available_types.count(synonym_name) == 0) {
		return false;
	}
	for (int i = 0; i < relation_name_to_available_types[synonym_name].first.size(); ++i) {
		if (relation_name_to_available_types[synonym_name].first[i] == type) {
			return true;
		}
	}
	return false;
}

bool QueryRelationTable::isValidRuleRight(string synonym_name, QNodeType type) {
	if (relation_name_to_available_types.count(synonym_name) == 0) {
		return false;
	}
	for (int i = 0; i < relation_name_to_available_types[synonym_name].second.size(); ++i) {
		if (relation_name_to_available_types[synonym_name].second[i] == type) {
			return true;
		}
	}
	return false;
}

/*
void QueryTable::addEntry(string condition, string array1[], string array2[], int len1 , int len2, int len3, int len4){
	arg_type_list arg1_list,arg2_list;
    arg1_list.synonym_type.assign(array1 + len1 ,array1 + len2);
    arg2_list.synonym_type.assign(array2 + len3 ,array2 + len4);
	entry e = {arg1_list,arg2_list};
	table[condition] = e;
}
*/
