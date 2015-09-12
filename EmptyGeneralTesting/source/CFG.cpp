#include "CFG.h"

/* Inner Graph Implementation */
GNode* CFG::innerGraph::getRoot() {
	return graphRoot;
}

GNode* CFG::innerGraph::getGNode(PROGLINE line) {
	return lineToNode[line];
}


/* CFG Class Implementation */
CFG::innerGraph* CFG::initProcCFG(PROCINDEX proc) {
	procToCFG[proc] = new innerGraph;
	return procToCFG[proc];
}

vector<CFG::innerGraph*> CFG::getAllCFG() {
	vector<CFG::innerGraph*> allCFG;
	std::map<PROCINDEX, innerGraph*>::iterator it;
	for (it = procToCFG.begin(); it != procToCFG.end(); ++it) {
		allCFG.push_back(it->second);
	}
	return allCFG;
}


/*DEPRECATED: Need to refactor and use the implementation above */
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