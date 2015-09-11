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

vector<VARINDEX> Modifies::getModifiedByStmt(STMTLINE stmtLine) {
    return stmtToVar.toVector(stmtLine);
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
