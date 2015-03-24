#pragma once
#include "GlobalType.h"
#include <string>
#include <vector>

class TNode{
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
	TNode(TType,string);
	~TNode(void);

	TType getTType();
	bool isTType(TNode node, TType type);
	bool setLeftSibling(TNode leftSibling);
	bool setRightSibling(TNode rightSibling);
	TNode* getLeftSibling();
	TNode* getRightSibling();
	bool setParentNode(TNode parentNode);
	TNode* getParentNode();
	bool addChild(TNode child);
	vector<TNode*> getChildren();
	bool setStmtLine(STMTLINE stmtNo);
	STMTLINE getStmtLine();
	string getValue();
};