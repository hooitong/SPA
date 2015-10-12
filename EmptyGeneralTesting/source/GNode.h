#pragma once

#include "GlobalType.h"
#include <vector>
#include <algorithm>

class GNode {
private:
  PROGLINE lineNumber;
  PROCINDEX procIndex;
  vector<GNode*> forwardNodes;
  vector<GNode*> backNode;
  GNode* branchBackNode;	//for CFGBip

public:
  GNode(PROGLINE lineNumber, PROCINDEX procIndex);
  ~GNode(void);

  PROGLINE getLineNumber();
  PROCINDEX getProcIndex();
  vector<GNode*> getForwardNodes();
  void getAllPossibleForwardNodes(STMTLINE start, bool rec, vector<GNode*> &result);
  vector<GNode*> getPrevNode();
  void addForwardNode(GNode* forward);
  void addPrevNode(GNode* prev);
  void clearForwardNode();	//for CFGBip
  void setBranchBackNode(GNode* node);	//for CFGBip
  GNode* getBranchBackNode();	//for CFGBip
};