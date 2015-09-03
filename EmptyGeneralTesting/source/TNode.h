#pragma once

#include <string>
#include <vector>

#include "GlobalType.h"

class TNode {
  private:
    string value;
    STMTLINE stmtNumber;
    TNode* parentNode;
    vector<TNode*> childrenNodes;
    TNode* leftSiblingNode;
    TNode* rightSiblingNode;
    TType type;

  public:
    TNode(void);
	TNode(bool);
    ~TNode(void);

    TType getTType();
    string getValue();
    bool setLeftSibling(TNode* leftSibling);
    bool setRightSibling(TNode* rightSibling);
    TNode* getLeftSibling();
    TNode* getRightSibling();
    bool setParentNode(TNode* parentNode);
    TNode* getParentNode();
    bool addChild(TNode* child);
	void setChildren(vector<TNode*> children);
    vector<TNode*> getChildren();
    bool setStmtLine(STMTLINE stmtNo);
	void setNodeValue(string s);
	void setTType(TType);
    STMTLINE getStmtLine();

	void print(int lvl);
};