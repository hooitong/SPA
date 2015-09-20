#include "Modifies.h"

/* Constructor & Destructor */
Modifies::Modifies(void) {
}

Modifies::~Modifies(void) {
}

void Modifies::setModifiesStmt(VARINDEX varIndex, STMTLINE stmt) {
  varToStmt.putRelation(varIndex, stmt);
  stmtToVar.putRelation(stmt, varIndex);
}

void Modifies::setModifiesProc(PROCINDEX procIndex, VARINDEX varIndex) {
  procToVar.putRelation(procIndex, varIndex);
  varToProc.putRelation(varIndex, procIndex);
}

bool Modifies::isModifiesForStmt(STMTLINE stmt, VARINDEX varIndex) {
  return stmtToVar.containsChild(stmt, varIndex);
}

bool Modifies::isModifiesForProc(PROCINDEX procIndex, VARINDEX varIndex) {
  return procToVar.containsChild(procIndex, varIndex);
}

vector<VARINDEX> Modifies::getModifiedByStmt(STMTLINE stmt) {
  return stmtToVar.toVector(stmt);
}

vector<VARINDEX> Modifies::getModifiedByProc(PROCINDEX procIndex) {
  return procToVar.toVector(procIndex);
}

vector<STMTLINE> Modifies::getModifiesForStmt(VARINDEX varIndex) {
  return varToStmt.toVector(varIndex);
}

vector<PROCINDEX> Modifies::getModifiesForProc(VARINDEX varIndex) {
  return varToProc.toVector(varIndex);
}
