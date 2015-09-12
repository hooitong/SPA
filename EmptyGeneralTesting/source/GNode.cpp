#include "GNode.h"

GNode::GNode(PROGLINE lineNumber) {
	this->lineNumber = lineNumber;
}

PROGLINE GNode::getLineNumber() {
	return lineNumber;
}

GNode* GNode::getNextMain() {
	return forwardMainNode;
}

GNode* GNode::getNextSide() {
	return forwardSideNode;
}

GNode* GNode::getPrev() {
	return backNode;
}

void GNode::setNextMain(GNode* main) {
	forwardMainNode = main;
}

void GNode::setNextSide(GNode* side) {
	forwardSideNode = side;
}

void GNode::setPrev(GNode* prev) {
	backNode = prev;
}