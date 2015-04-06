#pragma once

#include "GlobalType.h"
#include "Parent.h"

#include <vector>

class DesignExtractor {
  private:
    static DesignExtractor* deObj;
    void recursiveExtractParent(Parent* pObj, STMTLINE root, vector<STMTLINE> parents);

  public:
    DesignExtractor();
    ~DesignExtractor();
	static DesignExtractor* getInstance();
    void extractFollowsStar();
    void extractParentStar();
};