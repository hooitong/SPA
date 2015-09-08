#pragma once

#include "BitTable.h"
#include "GlobalType.h"

class CFG {

private:
	BitTable stmtToNextStmt;


public:
	
	void insert(STMTLINE from, STMTLINE to);
	vector<STMTLINE> getImmediateToStmts(STMTLINE from);
	void getAllToStmts(STMTLINE from, vector<STMTLINE> &result);

};
