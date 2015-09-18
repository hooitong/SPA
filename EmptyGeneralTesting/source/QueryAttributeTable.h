#pragma once

#include <string>
#include <map>
#include <vector>
#include "GlobalType.h"
using namespace std;

class QueryAttributeTable {
public:
	QueryAttributeTable(void);
	void addRule(QNodeType synonym_type, string attribute_name, RefType attribute_type);
	void addRule(QNodeType synonym_type, RefType reference_type);
	bool isValidRule(QNodeType synonym_type, string attribute_name);
	RefType getAttributeType(QNodeType synonym_type, string attribute_name);
	RefType getReferenceType(QNodeType);

private:
	map<QNodeType, vector<pair<string, RefType> > > synonym_type_to_available_attributes;
	map<QNodeType, RefType> synonym_type_to_reference_type;
};
