#include "CFG.h"


/* CFG Class Implementation */
void CFG::setProcToRoot(PROCINDEX proc, GNode* root) {
  procToRoot[proc] = root;
}

void CFG::setLineToNode(PROGLINE lineNumber, GNode* node) {
  lineToNode[lineNumber] = node;
}

vector<GNode*> CFG::getAllRootNodes() {
  vector<GNode*> allCFG;
  std::map<PROCINDEX, GNode*>::iterator it;
  for (it = procToRoot.begin(); it != procToRoot.end(); ++it) {
    allCFG.push_back(it->second);
  }
  return allCFG;
}


void CFG::insert(STMTLINE from, STMTLINE to, PROCINDEX procIndex) {
  GNode* nodeFrom;
  GNode* nodeTo;

  if (lineToNode.find(from) == lineToNode.end()) {
    //not found
    nodeFrom = new GNode(from);
    setLineToNode(from, nodeFrom);
  }
  else {
    nodeFrom = getGNode(from);
  }

  if (lineToNode.find(to) == lineToNode.end()) {
    //not found
    nodeTo = new GNode(to);
    setLineToNode(to, nodeTo);
  }
  else {
    nodeTo = getGNode(to);
  }

  if (procToRoot.find(procIndex) == procToRoot.end()) {
    //not found
    setProcToRoot(procIndex, nodeFrom);
  }

  nodeFrom->addForwardNode(nodeTo);
  nodeTo->addPrevNode(nodeFrom);

}

GNode* CFG::getGNode(PROGLINE line) {
  return lineToNode[line];
}

vector<GNode*> CFG::getAllGNodes() {
  vector<GNode*> allGNodes;
  std::map<STMTLINE, GNode*>::iterator it;
  for (it = lineToNode.begin(); it != lineToNode.end(); ++it) {
    allGNodes.push_back(it->second);
  }
  return allGNodes;
}