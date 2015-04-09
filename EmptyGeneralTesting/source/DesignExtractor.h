#pragma once

#include "GlobalType.h"
#include "Parent.h"

#include <vector>

class DesignExtractor {
  private:
    static void recursiveExtractParent(Parent* pObj, STMTLINE root, vector<STMTLINE> parents);
	static void extractFollowsStar();
	static void extractParentStar();
	static void extractModifiesContainer();
	static void extractUsesContainer();

	static bool isModifiesDuplicate(STMTLINE source, VARINDEX item);
	static bool isUsesDuplicate(STMTLINE source, VARINDEX item);

  public:
    DesignExtractor();
    ~DesignExtractor();
	static void extract();
};