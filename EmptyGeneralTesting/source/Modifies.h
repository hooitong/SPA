#pragma once
#include <vector>
#include "GlobalTypedef.h"
#include"TNode.h"


class Modifies
{
public:
	Modifies(void);
	~Modifies(void);

	bool setModifiesInPROC(PROCINDEX PROCINDEX, VARINDEX VARINDEX);
	bool setModifiesInStmt(STMTLINE stmt, VARINDEX VARINDEX);
	vector<VARINDEX> getModifiedByPROC(PROCINDEX PROCINDEX);
	vector<VARINDEX> getModifiedByStmt(STMTLINE STMTLINE);
	vector<TNode> getModifies(VARINDEX VARINDEX);



};

