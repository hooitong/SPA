#pragma once

#include "QNode.h"
#include <vector>

class QueryTree {
  private:
    QNode* queryRoot;

  public:
    QueryTree(void);
    ~QueryTree(void);

    QNode* createNode(QNodeType type, string name);
    void setAsRoot(QNode* node);
    void addChild(QNode* parent, QNode* child);
    vector<QNode*> getChildren(QNode* parent);
    QNode* getRoot(void);
    bool isEqual(QueryTree *anotherTree, bool print_debugging_message = false);
	void printTree(void);
};
