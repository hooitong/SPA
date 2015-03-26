#include "QNode.h"
#include "GlobalType.h"
#include <vector>

using namespace std;

QNode::QNode(void) {
}

QNode::QNode(QNodeType type, string name) {
    this->type = type;
    this->name = name;
}

QNode::~QNode(void) {
}

QNodeType QNode::getQType() {
    return this->type;
}

string QNode::getString() {
    return this->name;
}

vector<QNode*> QNode::getChildren(void) {
    return this->childrenNodes;
}

void QNode::addChild(QNode* node) {
    this->childrenNodes.push_back(node);
}