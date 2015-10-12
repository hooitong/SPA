#pragma once

#include "GlobalType.h"
#include "Parent.h"
#include "TNode.h"
#include "ParserUtils.h"

#include <vector>

class DesignExtractor {
  private:
    static void extractVariousRelationship(TNode* rootNode);
	static void extractInterprocedureCallStar();
	static void recursiveInterprocedureCallStar(PROCINDEX currentProc, PROCINDEX originalProc, bool first, vector<PROCINDEX> &result);
	static void extractInterprocedureModifiesUses();
	static void extractNext();
	static void constructCFGBip();

	static void getNodeEndPoints(TNode* node, vector<TNode*> &result);
	static void insertCFPAndCFGBip(STMTLINE from, STMTLINE to, PROCINDEX procIndex);
	static bool isPrimaryNode(TNode* node);


  public:
    DesignExtractor();
    ~DesignExtractor();
    static void extract();
};