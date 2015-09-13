#include "CFG.h"


/* CFG Class Implementation */
void CFG::setProcToRoot(PROCINDEX proc, GNode* root) {
	procToRoot[proc] = root;
}

void CFG::setLineToNode(PROGLINE lineNumber, GNode* node) {
	lineToNode[lineNumber] = node;
}

vector<GNode*> CFG::getAllRootNodes() {
	vector<GNode*> allCFG;
	std::map<PROCINDEX, GNode*>::iterator it;
	for (it = procToRoot.begin(); it != procToRoot.end(); ++it) {
		allCFG.push_back(it->second);
	}
	return allCFG;
}

GNode* CFG::getGNode(PROGLINE line) {
	return lineToNode[line];
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