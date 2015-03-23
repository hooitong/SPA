#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "GlobalType.h"

using namespace std;


class TNode;
class VarTable;

class PKB {
public:
	static VarTable* varTable; 
	static int setPROCToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);
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