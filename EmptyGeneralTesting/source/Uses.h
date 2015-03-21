#pragma once

#include <vector>
#include "TNode.h"

typedef int PROCINDEX, VARINDEX, STMTLine;
class Uses
{
public:
	Uses(void);
	~Uses(void);

	bool setUsesInProc(PROCINDEX procIndex, VARINDEX varIndex);
	bool setUsesInStmt(STMTLine stmtLine, VARINDEX varIndex);
	vector<VARINDEX> getUsedByProc (PROCINDEX procIndex);
	vector<VARINDEX> getUsedByStmt (STMTLine stmtLine);
	vector<TNode> getUses(VARINDEX varIndex);
};

