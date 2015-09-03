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

vector<VARINDEX> Modifies::getModifiedByStmt(STMTLINE stmtLine) {
    return stmtToVar.toVector(stmtLine);
}

vector<STMTLINE> Modifies::getModifies(VARINDEX varIndex) {
  return varToStmt.toVector(varIndex);
}