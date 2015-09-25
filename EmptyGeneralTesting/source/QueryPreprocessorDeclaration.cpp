#include "QueryPreprocessorDeclaration.h"
#include "QueryPreprocessor.h"
#include <string>
#include <iostream>
using namespace std;

QueryPreprocessorDeclaration::QueryPreprocessorDeclaration(string declaration_string) {
  fillNodeTypeTable();
  declaration_string = QueryPreprocessor::trim(declaration_string);
  isValid = true;
  if(declaration_string == "") {
    return;
  }
  int current_pointer = 0;
  while (true) {
    int next_semicolon = declaration_string.find(";", current_pointer);
    if (next_semicolon == string::npos) {
      //end of declaration
      return;
    }
    string declaration_clause = QueryPreprocessor::trim(declaration_string.substr(current_pointer, next_semicolon - current_pointer));
    processDeclarationClause(declaration_clause);
    if (!isValidDeclaration()) {
      return;
    }
    current_pointer = next_semicolon + 1;
  }
}

void QueryPreprocessorDeclaration::processDeclarationClause(string declaration_clause) {
  int space_pointer = declaration_clause.find(" ");
  string synonym_type = QueryPreprocessor::trim(declaration_clause.substr(0, space_pointer));
  if (!QueryPreprocessor::isDesignEntityType(synonym_type)) {
    isValid = false;
    return;
  }

  int current_pointer_clause = space_pointer + 1;
  bool end_of_clause = false;
  while (!end_of_clause) {
    int next_comma = declaration_clause.find(",", current_pointer_clause);
    if (next_comma == string::npos) {
      end_of_clause = true;
      next_comma = declaration_clause.length();
    }
    string synonym_name = QueryPreprocessor::trim(declaration_clause.substr(current_pointer_clause, next_comma - current_pointer_clause));
    if (isDeclaredSynonym(synonym_name) || !QueryPreprocessor::isIdent(synonym_name)) {
      isValid = false;
      return;
    } else {
      this->declareSynonym(synonym_type, synonym_name);
    }
    current_pointer_clause = next_comma + 1;
  }
}

QueryPreprocessorDeclaration::~QueryPreprocessorDeclaration(void) {
}

bool QueryPreprocessorDeclaration::isValidDeclaration(void) {
  return this->isValid;
}

bool QueryPreprocessorDeclaration::isDeclaredSynonym(string synonym) {
  return (this->synonym_to_type).count(synonym) > 0;
}

string QueryPreprocessorDeclaration::getSynonymType(string synonym) {
  if (!isDeclaredSynonym(synonym)) {
    return NULL;
  }
  return (this->synonym_to_type)[synonym];
}

QNode* QueryPreprocessorDeclaration::getSynonymTypeNode(string synonym) {
  if (!isDeclaredSynonym(synonym)) {
    return NULL;
  }
  if (string_type_to_node_type.count(getSynonymType(synonym)) == 0) {
    return NULL;
  }
  QNodeType node_type = string_type_to_node_type[getSynonymType(synonym)];
  return new QNode(node_type, synonym);
}

void QueryPreprocessorDeclaration::declareSynonym(string synonym_type, string synonym_name) {
  (this->synonym_to_type)[synonym_name] = synonym_type;
}

void QueryPreprocessorDeclaration::fillNodeTypeTable(void) {
  string_type_to_node_type["stmt"] = STMTSYNONYM;
  string_type_to_node_type["stmtLst"] = STMTLSTSYNONYM;
  string_type_to_node_type["assign"] = ASSIGNSYNONYM;
  string_type_to_node_type["while"] = WHILESYNONYM;
  string_type_to_node_type["variable"] = VARIABLESYNONYM;
  string_type_to_node_type["constant"] = CONSTSYNONYM;
  string_type_to_node_type["prog_line"] = PROGLINESYNONYM;
  string_type_to_node_type["procedure"] = PROCEDURESYNONYM;
  string_type_to_node_type["if"] = IFSYNONYM;
  string_type_to_node_type["call"] = CALLSYNONYM;
}
