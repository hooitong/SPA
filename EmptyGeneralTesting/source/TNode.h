#pragma once
#include <string>

using namespace std;

enum TNodeType {
	PROCEDURE_NODE,
	STMTLST_NODE,
	ASSIGN_NODE,
	VAR_NODE,
	CONST_NODE,
	PLUS_NODE,
	NONE
};

class TNode
{
public:
	TNode(void);
	~TNode(void);

	static TNode createTNode(TNodeType nodeType, string name);
	TNodeType getTType(TNode node);
	bool isTTYpe(TNode node, TNodeType type);
};