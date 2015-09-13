#include "GNode.h"

GNode::GNode(PROGLINE lineNumber) {
	this->lineNumber = lineNumber;
}

PROGLINE GNode::getLineNumber() {
	return lineNumber;
}

vector<GNode*> GNode::getForwardNodes() {
	return forwardNodes;
}

vector<GNode*> GNode::getPrevNode() {
	return backNode;
}

void GNode::addForwardNode(GNode* forward) {
	forwardNodes.push_back(forward);
}

void GNode::addPrevNode(GNode* prev) {
	backNode.push_back(prev);
}