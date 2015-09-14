#pragma once

#include "GlobalType.h"
#include "Parent.h"
#include "TNode.h"

#include <vector>

class DesignExtractor {
  private:
    static void extractVariousRelationship(TNode* rootNode);
	static void extractInterprocedureCallStar();
	static void recursiveInterprocedureCallStar(PROCINDEX currentProc, PROCINDEX originalProc, bool first, vector<PROCINDEX> &result);
	static void extractInterprocedureModifiesUses();
	static void extractNext();
	static bool isPrimitiveNode(TNode* node);

  public:
    DesignExtractor();
    ~DesignExtractor();
    static void extract();
};