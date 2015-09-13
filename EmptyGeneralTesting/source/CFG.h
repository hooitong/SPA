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
	GNode* getGNode(PROGLINE line);


/* Need to revise the API and implementation below to use the interface on the top.*/
private:
	BitTable stmtToNextStmt;

public:
	void insert(STMTLINE from, STMTLINE to, PROCINDEX procIndex);
	vector<STMTLINE> getImmediateToStmts(STMTLINE from);
	void getAllToStmts(STMTLINE from, vector<STMTLINE> &result);

};