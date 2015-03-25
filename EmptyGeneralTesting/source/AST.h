#pragma once

#include <vector>
#include <map>

#include "GlobalType.h"
#include "TNode.h"

class AST {
  private:
    std::map<STMTLINE, TNode*> stmtLine2NodeMap;
    TNode* procedureRoot; //temp solution until ProcTable is complete

  public:
    AST(void);
    ~AST(void);

    TNode* createTNode(TType nodeType, std::string value);
    bool setSibling(TNode leftNode, TNode rightNode);
    bool addChildTNode(TNode parent, TNode child);
    std::vector<TNode*> getChildren(TNode parent);
    TNode* getLeftSibling(TNode node);
    TNode* getRightSibling(TNode node);
    TNode* getParentTNode(TNode node);
    TNode* getTNode(STMTLINE line);
    bool setRoot(TNode root);
    TNode* getRoot();
    std::string getValue(TNode node);
    bool setStmtLine(TNode node, STMTLINE stmtNumber);
};
