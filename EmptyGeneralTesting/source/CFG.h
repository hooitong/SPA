#pragma once

#include "BitTable.h"
#include "GlobalType.h"
#include "GNode.h"

/* This class is a collective class that contains information of all CFG found in the program */
class CFG {
public:
	/* Inner class represents a single control flow graph for a procedure */
	class innerGraph {
	private:
		GNode* graphRoot;
		std::map<PROGLINE, GNode*> lineToNode;

	public:
		GNode* getRoot();
		GNode* getGNode(PROGLINE line);
	};

	innerGraph* initProcCFG(PROCINDEX proc);
	vector<innerGraph*> getAllCFG();

private:
	std::map<PROCINDEX, innerGraph*> procToCFG;
 

/* Need to revise the API and implementation below to use the interface on the top.*/
private:
	BitTable stmtToNextStmt;

public:
	void insert(STMTLINE from, STMTLINE to);
	vector<STMTLINE> getImmediateToStmts(STMTLINE from);
	void getAllToStmts(STMTLINE from, vector<STMTLINE> &result);

};