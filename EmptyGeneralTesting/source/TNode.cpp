#include "TNode.h"

/* Constructor & Destructor */
TNode::TNode(TType typeOfNode, string nodeValue) {
    stmtNumber = -1;
    type = typeOfNode;
    value = nodeValue;
}

TNode::TNode(void) {
    stmtNumber = -1;
}

TNode::~TNode(void) {
    delete parentNode;
    delete leftSiblingNode;
    delete rightSiblingNode;
    childrenNodes.clear();
}

TType TNode::getTType() {
    return type;
}

bool TNode::isTType(TNode node, TType type) {
    return (node.getTType()==type);
}

string TNode::getValue() {
    return value;
}

bool TNode::setLeftSibling(TNode leftSibling) {
    leftSiblingNode = &leftSibling;
    return true;
}

bool TNode::setRightSibling(TNode rightSibling) {
    rightSiblingNode = &rightSibling;
    return true;
}

TNode* TNode::getLeftSibling() {
    return leftSiblingNode;
}

TNode* TNode::getRightSibling() {
    return rightSiblingNode;
}

bool TNode::setParentNode(TNode node) {
    if(&parentNode) {
        return false;
        //already has parent, prevent it from resetting parent
    }
    parentNode = &node;
    return true;
}

TNode* TNode::getParentNode() {
    return parentNode;
}

bool TNode:: addChild(TNode node) {
    childrenNodes.push_back(&node);
    return true;
}

vector<TNode*> TNode::getChildren() {
    return childrenNodes;
}

bool TNode::setStmtLine(STMTLINE stmtNo) {
    this->stmtNumber = stmtNo;
    return true;
}

STMTLINE TNode::getStmtLine() {
    return stmtNumber;
}

