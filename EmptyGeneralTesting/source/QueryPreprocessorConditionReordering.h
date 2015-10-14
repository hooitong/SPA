#pragma once

#include "QNode.h"

typedef int (*ScoreFunction)(QNode*);

class QueryPreprocessorConditionReordering {
public:
  QueryPreprocessorConditionReordering();
  void sortConditions(QNode* condition_list_node);
  
private:
  static int alwaysReturnsFour(QNode* condition_node);
  static int numberOfSynonyms(QNode* condition_node);
  static int relationTypeScore(QNode* condition_node);
  int computeScore(QNode* condition_node);
  static bool isSynonym(QNode* condition_child_node);
  static vector<QNode*> getSynonymChildren(QNode* condition_node);
  void groupCommonSynonym(QNode* condition_list_node);
  bool isShareCommonSynonym(QNode* condition_node_one, QNode* condition_node_two);


  vector<ScoreFunction> score_functions;
  vector<int> score_weights;
};