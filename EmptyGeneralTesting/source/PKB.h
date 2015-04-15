#pragma once

#include "GlobalType.h"
#include "VarTable.h"
#include "AST.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"

class PKB {
  private:
    static PKB* pkbInstance;

    VarTable* varTable;
    AST* ast;
    Follows* follows;
    Parent* parent;
    Modifies* modifies;
    Uses* uses;

  public:
    /* Static method to retrieve singleton instance */
    static PKB* getPKB();

    /* Accessors methods to Design Abstractions in PKB */
    PKB();
    ~PKB();
    VarTable* getVarTable();
    AST* getAst();
    Follows* getFollows();
    Parent* getParent();
    Modifies* getModifies();
    Uses* getUses();
};