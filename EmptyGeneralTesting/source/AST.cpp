#include "AST.h"


AST::AST(void)
{
}

bool setSibling(TNode leftNode, TNode rightNode)
{
	return false;
}

bool addChildTNode(TNode parent, TNode child)
{
	return false;
}

vector<TNode> getChildren(TNode parent)
{
	vector<TNode> children;
	return children;
}

TNode getTChildNode(TNode parent, int children)
{
	return TNode();
}

TNode getLeftSibling(TNode node)
{
	return TNode();
}

TNode getRightSibling(TNode node)
{
	return TNode();
}

TNode getParentTNode(TNode node)
{
	return TNode();
}

GNode getGNode(TNode node)
{
	return GNode();
}

bool setGNode(TNode tNode, GNode gNode)
{
	return false;
}

TNode getTNode(STMTLine line)
{
	return TNode();
}

bool setRoot(TNode root)
{
	return false;
}

TNode getRoot()
{
	return TNode();
}

string getValue(TNode node)
{
	return "";
}


AST::~AST(void)
{
}
