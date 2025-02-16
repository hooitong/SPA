#include "QueryTree.h"

#include <vector>

QueryTree::QueryTree(void) {
}

QueryTree::~QueryTree(void) {
}

QNode* QueryTree::createNode(QNodeType type, string name) {
    QNode* newNode = new QNode(type, name);
    return newNode;
}

void QueryTree::setAsRoot(QNode* node) {
    this->queryRoot = node;
}

void QueryTree::addChild(QNode* parent, QNode* child) {
    parent->addChild(child);
}

vector<QNode*> QueryTree::getChildren(QNode* parent) {
    return parent->getChildren();
}

QNode* QueryTree::getRoot(void) {
    return this->queryRoot;
}

bool QueryTree::isEqual(QueryTree* anotherTree, bool print_debugging_message) {
    return this->getRoot()->isEqualSubtree(anotherTree->getRoot(), print_debugging_message);
}

void QueryTree::printTree(void) {
     this->getRoot()->printTree();
}
