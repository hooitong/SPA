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

void Uses::setUsesProc(PROCINDEX procIndex, STMTLINE stmt) {
	procToVar.putRelation(procIndex, stmt);
	varToProc.putRelation(stmt, procIndex);
}

vector<VARINDEX> Uses::getUsedByStmt(STMTLINE stmtLine) {
    return stmtToVar.toVector(stmtLine);
}

vector<PROCINDEX> Uses::getUsedByProc(PROCINDEX proc) {
	return procToVar.toVector(proc);
}

vector<STMTLINE> Uses::getUses(VARINDEX varIndex) {
    return varToStmt.toVector(varIndex);
}