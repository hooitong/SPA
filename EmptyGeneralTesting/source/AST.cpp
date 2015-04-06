#include "AST.h"

#include <stack>
#include <stdlib.h>
#include "Parser.h"

/* Constructor & Destructor */
AST::AST(void) {
}

AST::~AST(void) {
}

TNode* AST::createTNode(TType nodeType, std::string value) {
    return new TNode(nodeType, value);
}

bool AST::setSibling(TNode* leftNode, TNode* rightNode) {
    if((*leftNode).getRightSibling() != NULL) {
        return false;
    }
    if((*rightNode).getLeftSibling() != NULL) {
        return false;
    }
    (*leftNode).setRightSibling(rightNode);
    (*rightNode).setLeftSibling(leftNode);
    return true;
}

bool AST::addChildTNode(TNode* parent, TNode* child) {
    if((*child).getParentNode() != NULL) {
        return false;
    }

    /* Set two-way link of parent and child */
    (*parent).addChild(child);
    (*child).setParentNode(parent);
    return true;
}

vector<TNode*> AST::getChildren(TNode* parent) {
    return (*parent).getChildren();
}

TNode* AST::getLeftSibling(TNode* node) {
    return (*node).getLeftSibling();
}

TNode* AST::getRightSibling(TNode* node) {
    return (*node).getRightSibling();
}

TNode* AST::getParentTNode(TNode* node) {
    return (*node).getParentNode();
}

TNode* AST::getTNode(STMTLINE line) {
    std::map<STMTLINE,TNode*>::iterator it = stmt2NodeMap.find(line);
    if(it == stmt2NodeMap.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

string AST::getValue(TNode* node) {
    return (*node).getValue();
}

bool AST::setStmtLine(TNode* node, STMTLINE stmtNumber) {
    stmt2NodeMap[stmtNumber] = node;
    (*node).setStmtLine(stmtNumber);
    return true;
}

bool AST::setRoot(TNode* root) {
    procedureRoot = root;
    return true;
}

TNode* AST::getRoot() {
    return procedureRoot;
}

void AST::addToStmtLineMap(TType type, STMTLINE stmtNumber) {
    TType2StmtMap.insert(std::pair<TType,STMTLINE>(type, stmtNumber));
}

vector<STMTLINE> AST::getStmtLines(TType type) {
    vector<STMTLINE> stmtList;
    if(type == TType::STMTN) {
        for(stmtIt = TType2StmtMap.begin(); stmtIt != TType2StmtMap.end(); ++stmtIt) {
            stmtList.push_back(stmtIt->second);
        }
    } else {
        stmtRet = TType2StmtMap.equal_range(type);
        for(stmtIt = stmtRet.first; stmtIt != stmtRet.second; ++stmtIt) {
            stmtList.push_back(stmtIt->second);
        }
    }
    return stmtList;
}

bool AST::isMatch(TNode* node, TType type) {
    return (*node).getTType() == type;
}

bool AST::matchLeftPattern(STMTLINE stmtRoot, VARINDEX varToMatch) {
    vector<TNode*> childList = getTNode(stmtRoot)->getChildren();
    if(childList.empty() && childList[0]->getTType() != VARN) {
        return false;
    } else {
        return std::atoi(childList[0]->getValue().c_str()) == varToMatch;
    }
}

bool AST::matchRightPattern(STMTLINE stmtRoot, std::string expression, bool strict) {
    TNode* astNode = getTNode(stmtRoot);
    TNode* queryExpression = Parser::buildExprAST(expression);

    vector<TNode*> depthTraversalOfAstNode = getDFS(astNode);
    vector<TNode*> depthTraversalOfQuery = getDFS(Parser::buildExprAST(expression));
    int lengthOfTraversedAST = depthTraversalOfAstNode.size();
    int lengthOfPattern = depthTraversalOfQuery.size();
    string traversedASTString = convertTNodeListValueToString(depthTraversalOfAstNode);
    string traversedQueryString = convertTNodeListValueToString(depthTraversalOfQuery);

    if(strict) {
        if(lengthOfTraversedAST != lengthOfPattern || traversedASTString != traversedQueryString ) {
            return false;
        }
        return true;
    } else {
        return traversedASTString.find(traversedQueryString) != string::npos;
    }
}

string AST::convertTNodeListValueToString(vector<TNode*> nodes) {
    string result;
    for(int i = 0 ; i < nodes.size(); i++) {
        TNode * currentNode = nodes[i];
        if(currentNode->getTType() == PLUSN) {
            result+="+";
        } else if(currentNode->getTType() == MINUSN) {
            result+="-";
        } else {
            result+=getValue(nodes[i]);
        }
    }
    return result;
}

vector<TNode*> AST::getDFS(TNode* node) {
    vector<TNode*> stack;
    stack.push_back(node);
    vector<TNode*> returnVector;
    vector<TNode*> discoveredNode;
    TNode* currentNode = node;

    while(stack.size() > 0) {
        //getting the last item
        currentNode = stack[stack.size()-1];
        stack.pop_back();
        if(!ifNodeVisited(discoveredNode, currentNode)) {
            discoveredNode.push_back(currentNode);
            returnVector.push_back(currentNode);
        }

        vector<TNode*> childrenList = currentNode->getChildren();
        if(childrenList.size() > 0) {
            TNode *leftChild = childrenList[0];
            TNode *rightChild = childrenList[1];

            //keep pushing right child first so when popping we always retrieve the left child
            if(rightChild != NULL)
                stack.push_back(rightChild);
            if(leftChild != NULL)
                stack.push_back(leftChild);
        }
    }
    return returnVector;
}

bool AST::ifNodeVisited(vector<TNode*> nodeList, TNode* node) {
    for(int i = 0; i < nodeList.size(); i++) {
        if(nodeList[i] == node) {
            return true;
        }
    }
    return false;
}