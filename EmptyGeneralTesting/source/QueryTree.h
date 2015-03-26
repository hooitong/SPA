#pragma once
#include "QNode.h"
#include <vector>

using namespace std;

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
};
