#pragma once
#include <vector>
#include "TNode.h"

typedef int ProcIndex, VarIndex, STMTLine;

class Uses
{
public:
	Uses(void);
	~Uses(void);

	bool setUsesInProc(ProcIndex ProcIndex, VarIndex VarIndex);
	bool setUsesInStmt(STMTLine stmtLine, VarIndex VarIndex);
	vector<VarIndex> getUsedByProc (ProcIndex ProcIndex);
	vector<VarIndex> getUsedByStmt (STMTLine stmtLine);
	vector<TNode> getUses(VarIndex VarIndex);
};

