#include "CFGBip.h"


/* CFGBip Class Implementation */
void CFGBip::setLineToNode(PROGLINE lineNumber, GNode* node) {
  lineToNode[lineNumber] = node;
}


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