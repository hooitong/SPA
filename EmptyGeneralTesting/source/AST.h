#pragma once

#include <vector>
#include <map>
#include <string>

#include "GlobalType.h"
#include "TNode.h"

class AST {
  private:
    std::map<STMTLINE, TNode*> stmt2NodeMap;
    std::multimap<TType, STMTLINE> TType2StmtMap;
    std::multimap<TType,STMTLINE>::iterator stmtIt;
    std::pair <std::multimap<TType,STMTLINE>::iterator, std::multimap<TType,STMTLINE>::iterator> stmtRet;
    TNode* rootNode; // only support 1 procedure at the current iteration.

  public:
    AST(void);
    ~AST(void);

	void setRelationShip(TNode* node);
	void setPKBRelationShips(TNode* rootNode);
	bool isPrimitiveNode(TNode* node);

    TNode* createTNode(TType nodeType, std::string value);
    bool setSibling(TNode* leftNode, TNode* rightNode);
    bool addChildTNode(TNode* parent, TNode* child);
    std::vector<TNode*> getChildren(TNode* parent);
    TNode* getLeftSibling(TNode* node);
    TNode* getRightSibling(TNode* node);
    TNode* getParentTNode(TNode* node);
    TNode* getTNode(STMTLINE line);
    bool setRoot(TNode* root);
    TNode* getRoot();
    std::string getValue(TNode* node);
    bool setStmtLine(TNode* node, STMTLINE stmtNumber);
    void addToStmtLineMap(TType type, STMTLINE stmtNumber);
    vector<STMTLINE> getStmtLines(TType type);
    bool isMatch(TNode* node, TType type);
    bool matchLeftPattern(STMTLINE stmtRoot, VARINDEX varToMatch);
    bool matchRightPattern(STMTLINE stmtRoot, std::string expression, bool strict);


    // private methods for pattern matching
    vector<TNode*> getDFS(TNode* node);
    string convertTNodeListValueToString(vector<TNode*> nodes);
    bool ifNodeVisited(vector<TNode*> nodeList, TNode* node);





};
