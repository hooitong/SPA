#include "AST.h"


AST::AST(void)
{
}

bool AST:: setSibling(TNode leftNode, TNode rightNode){
	if(leftNode.getRightSibling()!=NULL){
		return false;
	}
	if(rightNode.getLeftSibling()!=NULL){
		return false;
	}
	leftNode.setRightSibling(rightNode);
	rightNode.setLeftSibling(leftNode);
	return true;
}

bool AST::addChildTNode(TNode parent, TNode child){
	if(child.getParentNode()!=NULL){
		return false;
	}

	child.setParentNode(parent);
	return true;
}



vector<TNode*> AST::getChildren(TNode parent){
	return parent.getChildren();
}


vector<TNode*> AST::getTChildrenNode(TNode parent, int children){
	//todo
}
TNode* AST::getLeftSibling(TNode node){
	return node.getLeftSibling();
}

TNode* AST::getRightSibling(TNode node){
	return node.getRightSibling();
}

TNode* AST::getParentTNode(TNode node){
	return node.getParentNode();
}

TNode getTNode(STMTLINE line){
	//todo
	return TNode();
}

bool setRoot(TNode root){
	root.setRoot(true);
	return root.isRoot();
}

TNode getRoot(){
	//todo
	return TNode();
}

string getValue(TNode node){
	//todo
	return "";
}


AST::~AST(void){
}
