#include "CFGBip.h"


/* CFGBip Class Implementation */
void CFGBip::setLineToNode(PROGLINE lineNumber, GNode* node) {
  lineToNode[lineNumber] = node;
}

//from and to must be within same procedure
void CFGBip::insert(STMTLINE from, STMTLINE to, PROCINDEX procIndex) {
  GNode* nodeFrom;
  GNode* nodeTo;

  if (lineToNode.find(from) == lineToNode.end()) {
    //not found
    nodeFrom = new GNode(from, procIndex);
    setLineToNode(from, nodeFrom);
	procIndexToNodes[procIndex].push_back(nodeFrom);

  }
  else {
    nodeFrom = getGNode(from);
  }

  if (lineToNode.find(to) == lineToNode.end()) {
    //not found
    nodeTo = new GNode(to, procIndex);
    setLineToNode(to, nodeTo);
	procIndexToNodes[procIndex].push_back(nodeTo);

  }
  else {
    nodeTo = getGNode(to);
  }

  nodeFrom->addForwardNode(nodeTo);
  nodeTo->addPrevNode(nodeFrom);
}

void CFGBip::insertBip(STMTLINE from, STMTLINE to, vector<STMTLINE> toProcEndNodeLineNumbers) {
  GNode* nodeFrom;
  GNode* nodeTo;

  if (lineToNode.find(from) == lineToNode.end()) {
    return;
  }
  else {
    nodeFrom = getGNode(from);
  }

  if (lineToNode.find(to) == lineToNode.end()) {
    return;
  }
  else {
    nodeTo = getGNode(to);
  }

	GNode* forwardNode = nodeFrom->getForwardNodes()[0];		//after CALLN can only be one forward node
	nodeFrom->clearForwardNode();
	nodeFrom->addForwardNode(nodeTo);
	nodeFrom->setBranchBackNode(forwardNode);

	for(int i = 0; i<toProcEndNodeLineNumbers.size(); i++){
		GNode* endNode = this->getGNode(toProcEndNodeLineNumbers[i]);
		endNode->addForwardNode(forwardNode);
	}
}


GNode* CFGBip::getGNode(PROGLINE line) {
  return lineToNode[line];
}

vector<GNode*> CFGBip::getAllGNodes() {
  vector<GNode*> allGNodes;
  std::map<STMTLINE, GNode*>::iterator it;
  for (it = lineToNode.begin(); it != lineToNode.end(); ++it) {
    allGNodes.push_back(it->second);
  }
  return allGNodes;
}

void CFGBip::setRootNode(GNode* root){
	this->rootNode = root;
}

GNode* CFGBip::getRootNode(){
	return this->rootNode;
}

vector<GNode*> CFGBip::getAllGNodesByProcIndex(PROCINDEX procIndex){
	return procIndexToNodes[procIndex];
}