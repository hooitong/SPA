#pragma once

#include <vector>
#include"TNode.h"

typedef int PROCINDEX, VARINDEX, STMTLine;

class Modifies
{
public:
	Modifies(void);
	~Modifies(void);

	bool setModifiesInProc(PROCINDEX procIndex, VARINDEX varIndex);
	bool setModifiesInStmt(STMTLine stmt, VARINDEX varIndex);
	vector<VARINDEX> getModifiedByProc(PROCINDEX procIndex);
	vector<VARINDEX> getModifiedByStmt(STMTLine stmtLine);
	vector<TNode> getModifies(VARINDEX varIndex);



};

