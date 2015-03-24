#pragma once
#include <vector>
#include <map>
#include "GlobalType.h"
#include "TNode.h"

class Modifies
{
private:
	std::multimap<VARINDEX,STMTLINE> var2StmtMap;
	std::multimap<VARINDEX,STMTLINE>::iterator varIt;
	std::pair <std::multimap<VARINDEX,STMTLINE>::iterator, std::multimap<VARINDEX,STMTLINE>::iterator> varRet;

	std::multimap<STMTLINE,VARINDEX> stmt2VarMap;
	std::multimap<STMTLINE,VARINDEX>::iterator stmtIt;
	std::pair <std::multimap<STMTLINE,VARINDEX>::iterator, std::multimap<STMTLINE,VARINDEX>::iterator> stmtRet;

public:
	Modifies(void);
	~Modifies(void);

	bool setModifiesStmt(VARINDEX varIndex, STMTLINE stmt);
	vector<VARINDEX> getModifiedByStmt(STMTLINE stmtLine);
	vector<STMTLINE> getModifies(VARINDEX varIndex);

	vector<VARINDEX> getModifiedByStmtWildCard();
	vector<STMTLINE> getModifiesWildCard();
};