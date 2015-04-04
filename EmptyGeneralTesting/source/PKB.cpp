#include "PKB.h"

PKB* PKB::pkbInstance;

PKB* PKB::getPKB() {
    if(pkbInstance == NULL) {
        pkbInstance = new PKB;
    }
    return pkbInstance;
}

/* Constructor & Destructor */
PKB::PKB(void) {
    varTable = new VarTable;
    ast = new AST;
    follows = new Follows;
    parent = new Parent;
    modifies = new Modifies;
    uses = new Uses;
}

PKB::~PKB(void) {
    /* Release all design abstraction back to the memory */
    delete varTable;
    delete ast;
    delete follows;
    delete parent;
    delete modifies;
    delete uses;
}

VarTable* PKB::getVarTable() {
    return varTable;
}

AST* PKB::getAst() {
    return ast;
}

Follows* PKB::getFollows() {
    return follows;
}

Parent* PKB::getParent() {
    return parent;
}

Modifies* PKB::getModifies() {
    return modifies;
}

Uses* PKB::getUses() {
    return uses;
}