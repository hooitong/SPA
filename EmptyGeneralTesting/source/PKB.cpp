#include "PKB.h"

PKB* PKB::pkbInstance;

PKB* PKB::getPKB() {
  if (pkbInstance == NULL) {
    pkbInstance = new PKB;
  }
  return pkbInstance;
}

void PKB::deletePKB() {
  pkbInstance = NULL;
}

/* Constructor & Destructor */
PKB::PKB(void) {
  varTable = new VarTable;
  ast = new AST;
  cfg = new CFG;
  follows = new Follows;
  parent = new Parent;
  modifies = new Modifies;
  uses = new Uses;
  calls = new Calls;
  procTable = new ProcTable;
  next = new Next;
  constTable = new ConstTable;
  cfgBip = new CFGBip;
  nextBip = new Next;
  sibling = new Sibling;
  contains = new Contains;
}

PKB::~PKB(void) {
  /* Release all design abstraction back to the memory */
  delete varTable;
  delete ast;
  delete cfg;
  delete follows;
  delete parent;
  delete modifies;
  delete uses;
  delete calls;
  delete procTable;
  delete next;
  delete constTable;
  delete cfgBip;
  delete nextBip;
  delete sibling;
  delete contains;
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

ProcTable* PKB::getProcTable() {
  return procTable;
}

Calls* PKB::getCalls() {
  return calls;
}

CFG* PKB::getCfg() {
  return cfg;
}

CFGBip* PKB::getCfgBip() {
  return cfgBip;
}

Next* PKB::getNext() {
  return next;
}

Next* PKB::getNextBip() {
  return nextBip;
}

ConstTable* PKB::getConstTable(){
  return constTable;
}

Sibling* PKB::getSibling(){
  return sibling;
}

Contains* PKB::getContains(){
  return contains;
}

vector<TNode*> PKB::getAllStmtLstNodes(){
	vector<TNode*> results;
	this->getPKB()->getAst()->getRoot()->getAllChildrenIncludeSubByTType(results, STMTLSTN);
	return results;
}