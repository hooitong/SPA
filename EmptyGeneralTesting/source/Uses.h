#pragma once
#include <vector>
#include <map>
#include "GlobalTypedef.h"
#include "TNode.h"

class Uses
{
private:
	static std::multimap<STMTLINE,VARINDEX> stmt2VarMap;
	static std::multimap<STMTLINE,VARINDEX>::iterator it;
	static std::pair <std::multimap<STMTLINE,VARINDEX>::iterator, std::multimap<STMTLINE,VARINDEX>::iterator> ret;

public:
	Uses(void);
	~Uses(void);

	static bool setUsesStmt(VARINDEX varIndex, STMTLINE stmt);
	static vector<VARINDEX> getUsedByStmt(STMTLINE stmtLine);
	static vector<STMTLINE> getUses(VARINDEX varIndex);
};

