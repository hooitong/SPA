#include "CFG.h"

void CFG::insert(STMTLINE from, STMTLINE to){
	stmtToNextStmt.putRelation(from, to);
}

vector<STMTLINE> CFG::getImmediateToStmts(STMTLINE from){
	return stmtToNextStmt.toVector(from);
}

void CFG::getAllToStmts(STMTLINE from, vector<STMTLINE> &result){
	vector<STMTLINE> toStmts = stmtToNextStmt.toVector(from);
	for(int i =0; i<toStmts.size(); i++){
		result.push_back(toStmts[i]);
		this->getAllToStmts(toStmts[i], result);
	}
}