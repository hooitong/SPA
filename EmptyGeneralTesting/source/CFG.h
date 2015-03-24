#pragma once
#include "GlobalType.h"
#include <vector>
#include "GNode.h"

using namespace std;

class CFG
{
public:
	CFG(void);
	~CFG(void);

	GNode createGNode(PROGLINE nodeRoot);
	bool setStmtNumber(PROGLINE PROGLINE);
	bool addPROGLINE(GNode node, PROGLINE PROGLINE);
	GNode getGNode(PROGLINE PROGLINE);
	GNode getNextGNode(GNode current, bool getRight);
	GNode getPreviousGNode(GNode current, bool getRight);
	bool setNextGNode(GNode current, GNode next, bool direction);
	bool setPreviousGNode(GNode current, GNode prevous, bool direction);
	vector<PROGLINE> getAllLine(GNode node);
	bool setGRoot(GNode root);
	vector<GNode> getGRoots();
	bool isNext(PROGLINE firstLine, PROGLINE secondLine);
	bool isNextStar(PROGLINE firstLine, PROGLINE secondLine);
	vector<PROGLINE> getBefore(PROGLINE currentLine);
	vector<PROGLINE> getBeforeStar (PROGLINE currentLine);
	vector <PROGLINE> getNext(PROGLINE currentLine);
	vector <PROGLINE> getNextStar(PROGLINE currentLine);
};
