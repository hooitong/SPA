#include "QueryPreprocessorConditionReordering.h"
#include "GlobalType.h"
#include <algorithm>

QueryPreprocessorConditionReordering::QueryPreprocessorConditionReordering() {
  score_functions.push_back(alwaysReturnsFour);
  score_weights.push_back(1);
  score_functions.push_back(relationTypeScore);
  score_weights.push_back(10);
  score_functions.push_back(numberOfSynonyms);
  score_weights.push_back(100);
}

void QueryPreprocessorConditionReordering::sortConditions(QNode* condition_list_node) {
  vector<QNode*> condition_nodes = condition_list_node->getChildren();
  vector<pair<int, QNode*> > condition_nodes_and_scores;
  for (int i = 0; i < (int)condition_nodes.size(); ++i) {
    condition_nodes_and_scores.push_back(make_pair(computeScore(condition_nodes[i]), condition_nodes[i]));
  }
  std::sort(condition_nodes.begin(), condition_nodes.end());
  QNode* updated_condition_list_node = new QNode(CONDITIONLIST, "");
  for (int i = 0; i < (int)condition_nodes.size(); ++i) {
    updated_condition_list_node->addChild(condition_nodes_and_scores[i].second);
  }
  groupCommonSynonym(updated_condition_list_node);
  condition_list_node = updated_condition_list_node;
}

bool QueryPreprocessorConditionReordering::isSynonym(QNode* condition_child_node) {
  QNodeType synonym_types[] = {STMTSYNONYM,
                               STMTLSTSYNONYM,
                               ASSIGNSYNONYM,
                               WHILESYNONYM,
                               VARIABLESYNONYM,
                               CONSTSYNONYM,
                               PROGLINESYNONYM,
                               PROCEDURESYNONYM,
                               CALLSYNONYM,
                               IFSYNONYM};
  for (int i = 0; i < 10; ++i) {
    if (condition_child_node->getQType() == synonym_types[i]) {
      return true;
    }
  }
  return false;
}

vector<QNode*> QueryPreprocessorConditionReordering::getSynonymChildren(QNode* condition_node) {
  vector<QNode*> condition_child_nodes = condition_node->getChildren();
  vector<QNode*> synonym_child_nodes;
  for (int i = 0; i < (int)condition_child_nodes.size(); ++i) {
    if (isSynonym(condition_child_nodes[i])) {
      synonym_child_nodes.push_back(condition_child_nodes[i]);
    }
  }
  return synonym_child_nodes;
}

void QueryPreprocessorConditionReordering::groupCommonSynonym(QNode* condition_list_node) {
  vector<QNode*> condition_nodes = condition_list_node->getChildren();
  QNode* updated_condition_list_node = new QNode(CONDITIONLIST, "");
  vector<bool> used(condition_nodes.size());
  for (int i = 0; i < (int)condition_nodes.size(); ++i) {
    if (used[i]) {
      continue;
    }
    vector<QNode*> in_this_group;
    in_this_group.push_back(condition_nodes[i]);
    used[i] = 1;
    bool push_new_condition = true;
    while (push_new_condition) {
      push_new_condition = false;
      for (int j = i + 1; j < (int)condition_nodes.size(); ++j) {
        if (used[j]) {
          continue;
        }
        bool push_to_group = false;
        // check whether condition_nodes[j] has common synonym with anything in current group
        for (int k = 0; k < (int)in_this_group.size(); ++k) {
          if (isShareCommonSynonym(condition_nodes[j], in_this_group[k])) {
            push_to_group = true;
            break;
          }
        }
        // if it has
        if (push_to_group) {
          in_this_group.push_back(condition_nodes[j]);
          used[j] = true;
          push_new_condition = true;
          break;
        }
      }
    }
    for (int j = 0; j < (int)in_this_group.size(); ++j) {
      updated_condition_list_node->addChild(in_this_group[j]);
    }
  }
  condition_list_node = updated_condition_list_node;
}

bool QueryPreprocessorConditionReordering::isShareCommonSynonym(QNode* condition_node_one, QNode* condition_node_two) {
  vector<QNode*> synonym_node_one = getSynonymChildren(condition_node_one);
  vector<QNode*> synonym_node_two = getSynonymChildren(condition_node_two);
  for (int i = 0; i < (int)synonym_node_one.size(); ++i) {
    for (int j = 0; j < (int)synonym_node_two.size(); ++j) {
      if (synonym_node_one[i]->isEqualSubtree(synonym_node_two[j])) {
        return true;
      }
    }
  }
  return false;
}

// computes the score of a condition. the condition with least score will be computed first
int QueryPreprocessorConditionReordering::computeScore(QNode* condition_node) {
  int total_score = 0;
  for (int i = 0; i < (int)score_functions.size(); ++i) {
    total_score += score_functions[i](condition_node) * score_weights[i];
  }
  return total_score;
}

// Ordering based on relation type. Affects* comes last, lead by Affect, lead by Next*, lead by the rest
int QueryPreprocessorConditionReordering::relationTypeScore(QNode* condition_node) {
  if (condition_node->getString() == "Affect*") {
    return 4;
  }
  if (condition_node->getString() == "Affect") {
    return 3;
  }
  if (condition_node->getString() == "Next*") {
    return 2;
  }
  return 1;
}

int QueryPreprocessorConditionReordering::alwaysReturnsFour(QNode* condition_node) {
  return 4;
}

int QueryPreprocessorConditionReordering::numberOfSynonyms(QNode* condition_node) {
  return getSynonymChildren(condition_node).size();
}
