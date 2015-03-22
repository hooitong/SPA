#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"

using namespace std;

class AST
{
public:
	AST(void);
	~AST(void);

	bool setSibling(TNode leftNode, TNode rightNode);
	bool addChildTNode(TNode parent, TNode child);	
	vector<TNode*> getChildren(TNode parent);
	vector<TNode*> getTChildrenNode(TNode parent, int children);
	TNode* getLeftSibling(TNode node);
	TNode* getRightSibling(TNode node);
	TNode* getParentTNode(TNode node);
	TNode getTNode(STMTLINE line);
	bool setRoot(TNode root);
	TNode getRoot();
	string getValue(TNode node);
};

