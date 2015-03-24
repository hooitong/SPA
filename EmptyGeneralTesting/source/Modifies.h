#pragma once
#include <vector>
#include <map>
#include "GlobalType.h"
#include"TNode.h"

class Modifies
{
private:
	static std::multimap<STMTLINE,VARINDEX> stmt2VarMap;
	static std::multimap<STMTLINE,VARINDEX>::iterator it;
	static std::pair <std::multimap<STMTLINE,VARINDEX>::iterator, std::multimap<STMTLINE,VARINDEX>::iterator> ret;

public:
	Modifies(void);
	~Modifies(void);

	static bool setModifiesStmt(VARINDEX varIndex, STMTLINE stmt);
	static vector<VARINDEX> getModifiedByStmt(STMTLINE stmtLine);
	static vector<STMTLINE> getModifies(VARINDEX varIndex);
};
