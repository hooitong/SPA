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
