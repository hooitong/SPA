#pragma once

#include "GlobalType.h"
#include "Parent.h"
#include "TNode.h"

#include <vector>

class DesignExtractor {
  private:
    static void setPKBRelationShips(TNode* rootNode);
	static void setInterprocedureCallStar();
	static void recursiveInterprocedureCallStar(PROCINDEX currentProc, PROCINDEX originalProc, bool first, vector<PROCINDEX> &result);
	static void setInterprocedureModifiesUses();
	static bool isPrimitiveNode(TNode* node);

  public:
    DesignExtractor();
    ~DesignExtractor();
    static void extract();
};