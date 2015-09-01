#pragma once

#include <vector>

#include "BitTable.h"
#include "GlobalType.h"

class Modifies {
  private:
    BitTable varToStmt;
    BitTable stmtToVar;

  public:
    Modifies(void);
    ~Modifies(void);

    void setModifiesStmt(VARINDEX varIndex, STMTLINE stmt);
    vector<VARINDEX> getModifiedByStmt(STMTLINE stmtLine);
    vector<STMTLINE> getModifies(VARINDEX varIndex);
};