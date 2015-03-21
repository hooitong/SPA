#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"


class Uses
{
public:
	Uses(void);
	~Uses(void);

	bool setUsesInPROC(PROCINDEX PROCINDEX, VARINDEX VARINDEX);
	bool setUsesInStmt(STMTLINE STMTLINE, VARINDEX VARINDEX);
	vector<VARINDEX> getUsedByPROC (PROCINDEX PROCINDEX);
	vector<VARINDEX> getUsedByStmt (STMTLINE STMTLINE);
	vector<TNode> getUses(VARINDEX VARINDEX);
};

