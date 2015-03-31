#pragma once

#include "GlobalType.h"
#include "Parent.h"

#include <vector>

class DesignExtractor {
  private:
    void recursiveExtractParent(Parent* pObj, STMTLINE root, vector<STMTLINE> parents);

  public:
    DesignExtractor();
    ~DesignExtractor();
    void extractFollowsStar();
    void extractParentStar();
};