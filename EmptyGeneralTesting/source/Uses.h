#pragma once

#include <vector>
#include <map>

#include "BitTable.h"
#include "GlobalType.h"

class Uses {
  private:
    BitTable varToStmt;
    BitTable stmtToVar;

  public:
    Uses(void);
    ~Uses(void);

    void setUsesStmt(VARINDEX varIndex, STMTLINE stmt);
    vector<VARINDEX> getUsedByStmt(STMTLINE stmtLine);
    vector<STMTLINE> getUses(VARINDEX varIndex);
};
