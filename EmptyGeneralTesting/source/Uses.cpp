#include "Uses.h"
#include <vector>

/* Constructor & Destructor */
Uses::Uses(void) {
}

Uses::~Uses(void) {
}

void Uses::setUsesStmt(VARINDEX varIndex, STMTLINE stmt) {
  varToStmt.putRelation(varIndex, stmt);
  stmtToVar.putRelation(stmt, varIndex);
}

void Uses::setUsesProc(PROCINDEX procIndex, STMTLINE stmt) {
  procToVar.putRelation(procIndex, stmt);
  varToProc.putRelation(stmt, procIndex);
}

bool Uses::isUsesForStmt(STMTLINE stmt, VARINDEX varIndex) {
  return stmtToVar.containsChild(stmt, varIndex);
}

bool Uses::isUsesForProc(PROCINDEX proc, VARINDEX varIndex) {
  return procToVar.containsChild(proc, varIndex);
}

std::vector<VARINDEX> Uses::getUsedByStmt(STMTLINE stmt) {
  return stmtToVar.toVector(stmt);
}

vector<PROCINDEX> Uses::getUsedByProc(PROCINDEX proc) {
  return procToVar.toVector(proc);
}

vector<STMTLINE> Uses::getUsesForStmt(VARINDEX varIndex) {
  return varToStmt.toVector(varIndex);
}

vector<PROCINDEX> Uses::getUsesForProc(VARINDEX varIndex) {
  return varToProc.toVector(varIndex);
}