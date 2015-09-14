#pragma once

#include "BitTable.h"
#include "GlobalType.h"
#include "GNode.h"

/* This class is a collective class that contains information of all CFG found in the program */
class CFG {

private:
	std::map<PROCINDEX, GNode*> procToRoot;
	std::map<PROGLINE, GNode*> lineToNode;

public:
	void setProcToRoot(PROCINDEX proc, GNode* root);
	void setLineToNode(PROGLINE lineNumber, GNode* node);
	vector<GNode*> getAllRootNodes();
	vector<GNode*> getAllGNodes();
	GNode* getGNode(PROGLINE line);
	void insert(STMTLINE from, STMTLINE to, PROCINDEX procIndex);


};