#include "Uses.h"

/* Constructor & Destructor */
Uses::Uses(void) {
}

Uses::~Uses(void) {
}

void Uses::setUsesStmt(VARINDEX varIndex, STMTLINE stmt) {
    varToStmt.putRelation(varIndex, stmt);
    stmtToVar.putRelation(stmt, varIndex);
}

vector<VARINDEX> Uses::getUsedByStmt(STMTLINE stmtLine) {
    return stmtToVar.toVector(stmtLine);
}

vector<STMTLINE> Uses::getUses(VARINDEX varIndex) {
    return varToStmt.toVector(varIndex);
}