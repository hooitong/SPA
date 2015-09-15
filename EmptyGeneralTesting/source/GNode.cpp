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

void GNode::getAllPossibleForwardNodes(STMTLINE start, bool rec, vector<GNode*> &results){
	if(forwardNodes.size() == 0 || (lineNumber == start && rec)){
		return;
	}
	else{
		for(int i = 0; i < forwardNodes.size(); i ++){
			if(find(results.begin(), results.end(), forwardNodes[i]) == results.end()) {
				results.push_back(forwardNodes[i]);
				forwardNodes[i]->getAllPossibleForwardNodes(start, true, results);
			}
		}
	}

}
