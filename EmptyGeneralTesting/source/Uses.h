#pragma once
#include <vector>
#include <map>
#include "GlobalType.h"
#include "TNode.h"

class Uses
{
private:
	std::multimap<VARINDEX,STMTLINE> var2StmtMap;
	std::multimap<VARINDEX,STMTLINE>::iterator varIt;
	std::pair <std::multimap<VARINDEX,STMTLINE>::iterator, std::multimap<VARINDEX,STMTLINE>::iterator> varRet;

	std::multimap<STMTLINE,VARINDEX> stmt2VarMap;
	std::multimap<STMTLINE,VARINDEX>::iterator stmtIt;
	std::pair <std::multimap<STMTLINE,VARINDEX>::iterator, std::multimap<STMTLINE,VARINDEX>::iterator> stmtRet;

public:
	Uses(void);
	~Uses(void);

	bool setUsesStmt(VARINDEX varIndex, STMTLINE stmt);
	vector<VARINDEX> getUsedByStmt(STMTLINE stmtLine);
	vector<STMTLINE> getUses(VARINDEX varIndex);

	vector<VARINDEX> getUsedByStmtWildCard();
	vector<STMTLINE> getUsesWildCard();
};
