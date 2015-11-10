#pragma once

#include "GlobalType.h"
#include "Parent.h"
#include "TNode.h"
#include "ParserUtils.h"
#include "Gnode.h"

#include <vector>

class DesignExtractor {
  private:
    static void extractVariousRelationship(TNode* rootNode);
	static void extractInterprocedureCallStar();
	static void recursiveInterprocedureCallStar(PROCINDEX currentProc, bool first, vector<PROCINDEX> &result);
	static void extractInterprocedureModifiesUses();
	static void extractNext();
	static void constructCFGBip();
	static void extractNextBip();
	static void nextBipSkipDummyGetAllToLinesRec(GNode* node, vector<STMTLINE> &result);

	static void getNodeEndPoints(TNode* node, vector<TNode*> &result);
	static void insertCFPAndCFGBip(STMTLINE from, STMTLINE to, PROCINDEX procIndex);
	static bool isPrimaryNode(TNode* node);
	static void getNextBipOfLastNode(TNode* node, vector<GNode*> &result);

  public:
    DesignExtractor();
    ~DesignExtractor();
    static void extract();
};