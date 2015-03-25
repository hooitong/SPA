#include "AST.h"

/* Constructor & Destructor */
AST::AST(void) {
}

AST::~AST(void) {
}

TNode* AST::createTNode(TType nodeType, std::string value) {
    return new TNode(nodeType, value);
}

bool AST::setSibling(TNode leftNode, TNode rightNode) {
    if(leftNode.getRightSibling()!= NULL) {
        return false;
    }
    if(rightNode.getLeftSibling()!= NULL) {
        return false;
    }
    leftNode.setRightSibling(rightNode);
    rightNode.setLeftSibling(leftNode);
    return true;
}

bool AST::addChildTNode(TNode parent, TNode child) {
    if(child.getParentNode()!= NULL) {
        return false;
    }

    /* Set two-way link of parent and child */
    parent.addChild(child);
    child.setParentNode(parent);
    return true;
}

vector<TNode*> AST::getChildren(TNode parent) {
    return parent.getChildren();
}

TNode* AST::getLeftSibling(TNode node) {
    return node.getLeftSibling();
}

TNode* AST::getRightSibling(TNode node) {
    return node.getRightSibling();
}

TNode* AST::getParentTNode(TNode node) {
    return node.getParentNode();
}

TNode* AST::getTNode(STMTLINE line) {
    std::map<STMTLINE,TNode*>::iterator it = stmtLine2NodeMap.find(line);
    if(it == stmtLine2NodeMap.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

string AST::getValue(TNode node) {
    return node.getValue();
}

bool AST::setStmtLine(TNode node, STMTLINE stmtNumber) {
    stmtLine2NodeMap[stmtNumber] = &node;
    node.setStmtLine(stmtNumber);
    return true;
}

bool AST::setRoot(TNode root) {
    procedureRoot = &root;
    return true;
}

TNode* AST::getRoot() {
    return procedureRoot;
}