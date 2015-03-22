#pragma once
#include <vector>
#include <map>
#include "GlobalTypedef.h"
#include "TNode.h"

using namespace std;

struct varInfo{
	VARINDEX var_index;
	VARNAME var_name;
	std::vector<TNode*> modified_by;
	std::vector<TNode*> used_by;	
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
	static bool addModifiedBy(VARINDEX varIndex, TNode* node);
	static bool addUsedBy (VARINDEX varIndex, TNode* node);
	static vector<TNode*> getModifiedBy(VARINDEX varIndex);
	static vector<TNode*> getUsedBy(VARINDEX varIndex);

};

