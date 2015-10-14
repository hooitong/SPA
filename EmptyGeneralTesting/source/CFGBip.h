#pragma once

#include "BitTable.h"
#include "GlobalType.h"
#include "GNode.h"

/* This class is a collective class that contains information of all CFGBip found in the program */
class CFGBip {
private:
  std::map<PROGLINE, GNode*> lineToNode;
  std::map<PROCINDEX, vector<GNode*>> procIndexToNodes;
  GNode* rootNode;

public:
  void setLineToNode(PROGLINE lineNumber, GNode* node);
  vector<GNode*> getAllGNodes();
  vector<GNode*> getAllGNodesByProcIndex(PROCINDEX procIndex);
  GNode* getGNode(PROGLINE line);
  void insert(STMTLINE from, STMTLINE to, PROCINDEX procIndex);
  void insertBip(STMTLINE from, STMTLINE to, vector<STMTLINE> toProcEndNodeLineNumbers);
  void setRootNode(GNode* root);
  GNode* getRootNode();
};