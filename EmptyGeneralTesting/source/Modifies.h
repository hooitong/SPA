#pragma once
#include <vector>
#include"TNode.h"

typedef int ProcIndex, VarIndex, STMTLine;

class Modifies
{
public:
	Modifies(void);
	~Modifies(void);

	bool setModifiesInProc(ProcIndex ProcIndex, VarIndex VarIndex);
	bool setModifiesInStmt(STMTLine stmt, VarIndex VarIndex);
	vector<VarIndex> getModifiedByProc(ProcIndex ProcIndex);
	vector<VarIndex> getModifiedByStmt(STMTLine stmtLine);
	vector<TNode> getModifies(VarIndex VarIndex);



};

