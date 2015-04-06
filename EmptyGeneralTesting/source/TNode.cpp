#include "TNode.h"

/* Constructor & Destructor */
TNode::TNode(TType typeOfNode, string nodeValue) {
    stmtNumber = -1;
    type = typeOfNode;
    value = nodeValue;
    parentNode = NULL;
    leftSiblingNode = NULL;
    rightSiblingNode = NULL;
}

TNode::TNode(void) {
    stmtNumber = -1;
}

//The destructor should be first called by the root of the AST.
TNode::~TNode(void) {
    delete rightSiblingNode;
    childrenNodes.clear();
}

TType TNode::getTType() {
    return type;
}

string TNode::getValue() {
    return value;
}

bool TNode::setLeftSibling(TNode* leftSibling) {
    leftSiblingNode = leftSibling;
    return true;
}

bool TNode::setRightSibling(TNode* rightSibling) {
    rightSiblingNode = rightSibling;
    return true;
}

TNode* TNode::getLeftSibling() {
    return leftSiblingNode;
}

TNode* TNode::getRightSibling() {
    return rightSiblingNode;
}

bool TNode::setParentNode(TNode* node) {
    if(parentNode!=NULL) {
        return false;
        //already has parent, prevent it from resetting parent
    }
    parentNode = node;
    return true;
}

TNode* TNode::getParentNode() {
    return parentNode;
}

bool TNode:: addChild(TNode* node) {
    childrenNodes.push_back(node);
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