#include "TNode.h"


TNode::TNode(void){
}
TNode::TNode(TType typeOfNode, string nodeValue){
	type = typeOfNode;
	value = nodeValue;
}

bool TNode:: addChild(TNode node){
	childrenNodes.push_back(&node);
	return true;
}

bool TNode::setParentNode(TNode node){
	if(&parentNode){
		return false;
		//already has parent, prevent it from resetting parent
	}
	parentNode = &node;
	return true;
}

TNode* TNode::getParentNode() {
	return parentNode;
}

bool TNode::setLeftSibling(TNode leftSibling){
	leftSiblingNode = &leftSibling;
	return true;	
}

bool TNode::setRightSibling(TNode rightSibling){
	rightSiblingNode = &rightSibling;
	return true;	
}

TNode* TNode::getLeftSibling(){
	return leftSiblingNode;
}

TNode* TNode::getRightSibling(){
	return rightSiblingNode;
}

TNode::~TNode(void){
	type = NONE;
	parentNode = NULL;
	childrenNodes.clear();
}

TType TNode::getTType() {
	return type;
}

bool TNode::isTType(TNode node, TType type){
	return (node.getTType()==type);
}

vector<TNode*> TNode:: getChildren(){
	return childrenNodes;
}

