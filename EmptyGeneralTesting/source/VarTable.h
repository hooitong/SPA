#pragma once
#include <vector>
#include "TNode.h"

using namespace std;

typedef short Proc;
typedef int VarIndex;
typedef string VarName;



class VarTable
{

private:

public:
	VarTable(void);
	~VarTable(void);

	static VarIndex insertVar(VarName VarName);
	static VarName getVarName(VarIndex VarIndex);
	static VarIndex getVarIndex(VarName VarName);
	static int getSize();
	static vector<VarIndex> getAllVar();
	static bool addModifiedBy(VarIndex var, TNode node);
	static bool addUsedBy (VarIndex var, TNode node);
	static vector<TNode> getModifiedBy(VarIndex var);
	static vector<TNode> getUsedBy(VarIndex var);

};

