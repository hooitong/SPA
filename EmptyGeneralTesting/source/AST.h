#pragma once
#include <vector>
#include <map>
#include "GlobalType.h"
#include "TNode.h"

class AST
{
private:
	static std::map<STMTLINE, TNode*> stmtLine2NodeMap;
	static TNode* procedureRoot; //temp solution until ProcTable is complete

public:
	AST(void);
	~AST(void);

	static TNode* createTNode(TType nodeType, std::string value);
	static bool setSibling(TNode leftNode, TNode rightNode);
	static bool addChildTNode(TNode parent, TNode child);
	static std::vector<TNode*> getChildren(TNode parent);
	static TNode* getLeftSibling(TNode node);
	static TNode* getRightSibling(TNode node);
	static TNode* getParentTNode(TNode node);
	static TNode* getTNode(STMTLINE line);
	static bool setRoot(TNode root);
	static TNode* getRoot();
	static std::string getValue(TNode node);
	static bool setStmtLine(TNode node, STMTLINE stmtNumber);
};
