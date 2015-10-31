#include "QueryAttributeTable.h"
#include "GlobalType.h"

QueryAttributeTable::QueryAttributeTable(void) {
  addRule(PROCEDURESYNONYM, "procName", REF_NAME);
  addRule(CALLSYNONYM, "procName", REF_NAME);
  addRule(VARIABLESYNONYM, "varName", REF_NAME);
  addRule(CONSTSYNONYM, "value", REF_INTEGER);
  addRule(STMTSYNONYM, "stmt#", REF_INTEGER);
  addRule(ASSIGNSYNONYM, "stmt#", REF_INTEGER);
  addRule(WHILESYNONYM, "stmt#", REF_INTEGER);
  addRule(IFSYNONYM, "stmt#", REF_INTEGER);
  addRule(CALLSYNONYM, "stmt#", REF_INTEGER);

  addRule(PROGLINESYNONYM, REF_INTEGER);
  addRule(CONST, REF_INTEGER);
}

void QueryAttributeTable::addRule(QNodeType synonym_type, string attribute_name, RefType attribute_type) {
  synonym_type_to_available_attributes[synonym_type].push_back(make_pair(attribute_name, attribute_type));
}

void QueryAttributeTable::addRule(QNodeType synonym_type, RefType reference_type) {
  synonym_type_to_reference_type[synonym_type] = reference_type;
}

bool QueryAttributeTable::isValidRule(QNodeType synonym_type, string attribute_name) {
  for (int i = 0; i < synonym_type_to_available_attributes[synonym_type].size(); ++i) {
	if (synonym_type_to_available_attributes[synonym_type][i].first == attribute_name) {
	  return true;
    }
  }
	return false;
}

RefType QueryAttributeTable::getAttributeType(QNodeType synonym_type, string attribute_name) {
  for (int i = 0; i < synonym_type_to_available_attributes[synonym_type].size(); ++i) {
    if (synonym_type_to_available_attributes[synonym_type][i].first == attribute_name) {
	  return synonym_type_to_available_attributes[synonym_type][i].second;
	}
  }
}

RefType QueryAttributeTable::getReferenceType(QNodeType synonym_type) {
  if (synonym_type_to_reference_type.count(synonym_type) > 0) {
    return synonym_type_to_reference_type[synonym_type];
  }
  return REF_NAME;
}
