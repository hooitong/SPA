#pragma once

#include <string>
#include <map>
#include <vector>
#include "GlobalType.h"
using namespace std;

class QueryRelationTable {
public:
	QueryRelationTable(void);
	void addRule(string relation_name, vector<QNodeType> available_left_types, vector<QNodeType> available_right_types);
	void addRuleLeft(string relation_name, vector<QNodeType> available_types);
	void addRuleRight(string relation_name, vector<QNodeType> available_types);
	bool isValidRule(string relation_name, QNodeType left_type, QNodeType right_type);
	bool isValidRuleLeft(string relation_name, QNodeType type);
	bool isValidRuleRight(string relation_name, QNodeType type);

private:
	map<string, pair<vector<QNodeType>, vector<QNodeType> > > relation_name_to_available_types;

};
