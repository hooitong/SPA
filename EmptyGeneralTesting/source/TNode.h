#pragma once
#include <string>
#include <vector>

using namespace std;

enum TType {
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
	string value;
	TNode* parentNode;
	vector<TNode*> childrenNodes;	
	TNode* leftSiblingNode;
	TNode* rightSiblingNode;
	TType type;

public:
	TNode(void);
	TNode(TType,string);
	~TNode(void);

	TType getTType();
	bool isTType(TNode node, TType type);
	bool setLeftSibling(TNode leftSibling);
	bool setRightSibling(TNode rightSibling);
	TNode* getLeftSibling();
	TNode* getRightSibling();
	bool setParentNode(TNode parentNode);
	TNode* getParentNode();
	bool addChild(TNode child);
	vector<TNode*> getChildren();


};