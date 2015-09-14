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

void GNode::getAllPossibleForwardNodes(STMTLINE start, vector<GNode*> &results){
	if(forwardNodes.size() == 0 || lineNumber == start){
		return;
	}
	else{
		for(int i = 0; i < forwardNodes.size(); i ++){
			results.push_back(forwardNodes[i]);
			forwardNodes[i]->getAllPossibleForwardNodes(start, results);
		}
	}

}
