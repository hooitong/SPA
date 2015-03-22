#pragma once
#include <string>
#include <vector>

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

class TNode{

private:
	string name;
	TNode* parentNode;
	vector<TNode*> childNodes;	
	vector<TNode*> siblingNodes;
	TNodeType type;

public:
	TNode(void);
	TNode(TNodeType,string);
	~TNode(void);

	TNodeType getTType();
	bool isTTYpe(TNode node, TNodeType type);
	bool addSibling(TNode siblingNode);
	vector<TNode*> getSiblingsNodes();
	TNode getNext();
	bool setParent(TNode parentNode);
};