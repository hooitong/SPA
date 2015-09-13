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

GNode* GNode::getPrevNode() {
	return backNode;
}

void GNode::addForwardNode(GNode* forward) {
	forwardNodes.push_back(forward);
}

void GNode::setPrevNode(GNode* prev) {
	backNode = prev;
}