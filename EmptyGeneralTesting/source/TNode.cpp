#include "TNode.h"


TNode::TNode(void){
}
TNode::TNode(TNodeType typeOfNode, string nodeName){
	type = typeOfNode;
	name = nodeName;
}

bool TNode::setParent(TNode node){
	if(&parentNode){
		return false;
		//already has parent, prevent it from resetting parent
	}
	parentNode = &node;
	return true;
}

bool TNode:: addSibling(TNode siblingNode){
	
	TNode::getSiblingsNodes().push_back(&siblingNode);
	return true;	
}

vector<TNode*> TNode::getSiblingsNodes(){
	return siblingNodes;
}

TNode::~TNode(void){
	type = NONE;
	parentNode = NULL;
	childNodes.clear();
	siblingNodes.clear();
}

TNodeType TNode::getTType() {
	return type;
}

bool TNode::isTTYpe(TNode node, TNodeType type){
	return (node.getTType()==type);
}