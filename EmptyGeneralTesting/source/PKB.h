#pragma once

#include "GlobalType.h"
#include "ConstTable.h"
#include "VarTable.h"
#include "AST.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"

class PKB{
private:
	VarTable* varTable;
	AST* ast;
	Follows* follows;
	Parent* parent;
	Modifies* modifies;
	Uses* uses;

public:
	/* Accessors methods to Design Abstractions */
	PKB();
	~PKB();
	VarTable* getVarTable();
	AST* getAst();
	Follows* getFollows();
	Parent* getParent();
	Modifies* getModifies();
	Uses* getUses();
};