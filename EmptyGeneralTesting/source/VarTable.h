#pragma once
#include <vector>
#include <map>
#include "GlobalType.h"
#include "TNode.h"

struct varInfo{
	VARINDEX var_index;
	VARNAME var_name;
	std::vector<STMTLINE> modified_by;
	std::vector<STMTLINE> used_by;	
};

class VarTable
{
private:
	static map<VARINDEX, varInfo> varIndexMap;
	static map<VARNAME, varInfo> varNameMap;
	static VARINDEX currentMapIndex;

public:
	VarTable(void);
	~VarTable(void);
	
	static VARINDEX insertVar(VARNAME varName);
	static VARNAME getVarName(VARINDEX varIndex);
	static VARINDEX getVarIndex(VARNAME varName);
	static int getSize();
	static vector<VARINDEX> getAllVarIndex();
	static vector<VARNAME> getAllVarName();
	static bool addModifiedBy(VARINDEX varIndex, STMTLINE node);
	static bool addUsedBy (VARINDEX varIndex, STMTLINE node);
	static vector<STMTLINE> getModifiedBy(VARINDEX varIndex);
	static vector<STMTLINE> getUsedBy(VARINDEX varIndex);
};

