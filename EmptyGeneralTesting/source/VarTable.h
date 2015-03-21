#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include "TNode.h"

using namespace std;




class VarTable
{

private:

public:
	VarTable(void);
	~VarTable(void);

	static VARINDEX insertVar(VARNAME VARNAME);
	static VARNAME getVARNAME(VARINDEX VARINDEX);
	static VARINDEX getVARINDEX(VARNAME VARNAME);
	static int getSize();
	static vector<VARINDEX> getAllVar();
	static bool addModifiedBy(VARINDEX var, TNode node);
	static bool addUsedBy (VARINDEX var, TNode node);
	static vector<TNode> getModifiedBy(VARINDEX var);
	static vector<TNode> getUsedBy(VARINDEX var);

};

