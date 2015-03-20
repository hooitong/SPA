#pragma once

#include <vector>

using namespace std;
typedef short PROC;
typedef int VARINDEX;
typedef string VARNAME;

class TNode;

class VarTable
{
public:
	VarTable(void);
	~VarTable(void);

	static VARINDEX insertVar(VARNAME varName);
	static VARNAME getVarName(VARINDEX varIndex);
	static VARINDEX getVarIndex(VARNAME varName);
	static int getSize();
	static vector<VARINDEX> getAllVar();
	static bool addModifiedBy(VARINDEX var, TNode node);
	static bool addUsedBy (VARINDEX var, TNode node);
	static vector<TNode> getModifiedBy(VARINDEX var);
	static vector<TNode> getUsedBy(VARINDEX var);

};

