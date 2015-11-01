#pragma once

#include <string>
#include <vector>

#include "GlobalType.h"

class QNode {
  private:
    QNodeType type;
    string name;
    vector<QNode*> childrenNodes;

  public:
    QNode(void);
    QNode(QNodeType, string);
    ~QNode(void);

    QNodeType getQType() const;
    string getString() const;
    vector<QNode*> getChildren() const;

    void addChild(QNode* node);
    bool isEqualSubtree(QNode *node) const;
	bool printTree();
};