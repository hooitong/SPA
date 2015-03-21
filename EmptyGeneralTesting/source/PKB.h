#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef short Proc;
typedef int VarIndex;
typedef string VarName;

class TNode;
class VarTable;

class PKB {
public:
	static VarTable* varTable; 
	static int setProcToAST(Proc p, TNode* r);
	static TNode* getRootAST (Proc p);
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