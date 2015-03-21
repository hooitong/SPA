#pragma once

typedef int STMTLine;
using namespace std;
#include <TNode.h>
#include <GNode.h>
#include <vector>

class AST
{
public:
	AST(void);
	~AST(void);

	bool setSibling(TNode leftNode, TNode rightNode);
	bool addChildTNode(TNode parent, TNode child);	
	vector<TNode> getChildren(TNode parent);
	TNode getTChildNode(TNode parent, int children);
	TNode getLeftSibling(TNode node);
	TNode getRightSibling(TNode node);
	TNode getParentTNode(TNode node);
	GNode getGNode(TNode node);
	bool setGNode(TNode tNode, GNode gNode);
	TNode getTNode(STMTLine line);
	bool setRoot(TNode root);
	TNode getRoot();
	string getValue(TNode node);
};

