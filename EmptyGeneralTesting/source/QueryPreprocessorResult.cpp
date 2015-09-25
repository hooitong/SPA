#include "QueryPreprocessorResult.h"
#include "QueryPreprocessor.h"
#include <string>
using namespace std;

QueryPreprocessorResult::QueryPreprocessorResult(QueryPreprocessorDeclaration* declaration) {
  this->declaration = declaration;
  attribute_table = new QueryAttributeTable();
  isValid = true;
}

QNode* QueryPreprocessorResult::getResultTree(string result_string) {
  QNode* result_root = new QNode(RESULTLIST, "");
  if (result_string.at(0) == '<' && result_string.at(result_string.length() - 1) == '>') {
    int current_position = 1;
    bool end_of_results = false;
    while (!end_of_results && isValid) {
      int next_comma_position = result_string.find(",", current_position);
      if (next_comma_position == string::npos) {
        end_of_results = true;
        next_comma_position = result_string.length() - 1;
      }
      string synonym_name = QueryPreprocessor::trim(result_string.substr(current_position, next_comma_position - current_position));
      QNode* result_node = getResultNode(synonym_name);
      result_root->addChild(result_node);
      current_position = next_comma_position + 1;
    }
  } else if (result_string == "BOOLEAN") {
    QNode* result_node = new QNode(BOOLEAN, "");
    result_root->addChild(result_node);
  } else {
    QNode* result_node = getResultNode(result_string);
    result_root->addChild(result_node);
  }
  return result_root;
}

QNode* QueryPreprocessorResult::getResultNode(string result_elem) {
  int dot_position = QueryPreprocessor::find(result_elem, ".");
  if (dot_position == string::npos) {
    if(declaration->isDeclaredSynonym(result_elem) && QueryPreprocessor::isElem(result_elem)) {
      return declaration->getSynonymTypeNode(result_elem);
    }
    isValid = false;
    return NULL;
  } else {
    string synonym_name = QueryPreprocessor::trim(result_elem.substr(0, dot_position));
    if (!declaration->isDeclaredSynonym(synonym_name) || !QueryPreprocessor::isElem(synonym_name)) {
      isValid = false;
      return NULL;
    }
    QNode* synonym_node = declaration->getSynonymTypeNode(synonym_name);
    string attribute_name = QueryPreprocessor::trim(result_elem.substr(dot_position + 1, result_elem.length() - (dot_position + 1)));
    if (attribute_table->isValidRule(synonym_node->getQType(), attribute_name)) {
      QNode* attribute_node = new QNode(ATTRIBUTE, attribute_name);
      synonym_node->addChild(attribute_node);
      return synonym_node;
    }
    isValid = false;
    return NULL;
  }
}

bool QueryPreprocessorResult::isValidResult(void) {
  return isValid;
}
