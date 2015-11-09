#include "ContainsEvaluator.h"
#include <sstream>

ContainsEvaluator::ContainsEvaluator(PKB* pkb) {
    this->pkb = pkb;
}

QueryResult ContainsEvaluator::solveConstConst(QNode* node) {
    istringstream leftss(node->getChildren()[0]->getString());
    istringstream rightss(node->getChildren()[1]->getString());
    int leftNode;
    int rightNode;
    leftss >> leftNode;
    rightss >> rightNode;
    TNode* leftTNode = pkb->getAst()->getTNode(leftNode);
    vector <TNode*> children = leftTNode->getChildren();
    for (vector<TNode*>::iterator it = children.begin();
        it != children.end(); it++) {

        if ((*it)->getStmtLine() == rightNode) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult ContainsEvaluator::solveConstSyn(QNode* node) {
    istringstream leftss(node->getChildren()[0]->getString());
    int leftStmt;
    leftss >> leftStmt;
    TNode* leftTNode = pkb->getAst()->getTNode(leftStmt);
    vector <TNode*> children = leftTNode->getChildren();
    vector <int> result;
    for (vector<TNode*>::iterator it = children.begin();
        it != children.end(); it++) {
        if (matchType(node->getChildren()[1]->getQType(), (*it)->getTType())) {
            result.push_back(toInt(*it));
        }
    }
    return QueryResult(result, node->getChildren()[1]->getString());
}

QueryResult ContainsEvaluator::solveSynConst(QNode* node) {
    istringstream rightss(node->getChildren()[1]->getString());
    int rightStmt;
    rightss >> rightStmt;
    TNode* rightNode = pkb->getAst()->getTNode(rightStmt);
    TNode* parent = rightNode->getParentNode();
    if (parent != NULL && matchType(node->getChildren()[0]->getQType(), parent->getTType())) {
        return QueryResult(toInt(parent), node->getChildren()[1]->getString());    
    } else {
        return QueryResult(false);
    }
}

QueryResult ContainsEvaluator::solveSynSyn(QNode* node) {
    vector <TNode*> nodes;
    vector <int> progIndex = pkb->getProcTable()->getAllProcIndex();

    for (vector<int>::iterator it = progIndex.begin(); it != progIndex.end(); it++) {
        getAllTNodesFrom(pkb->getAst()->getProcTNodeByIndex(*it);
    }
    vector <pair<int,int> > results;
    for (vector<TNode*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        if (matchType(node->getChildren()[0]->getQType(), (*it)->getTType())) {
            vector <TNode*> children = (*it)->getChildren();
            for (vector<TNode*>::iterator it2 = children.begin(); it2 != children.end(); it2++) {
                if (matchType(node->getChildren()[1]->getQType(), (*it2)->getTType())) {
                    results.push_back(make_pair(toInt(*it), toInt(*it2)));
                }
            }
        }
    }
    return QueryResult(results, node->getChildren()[0]->getString(), node->getChildren()[1]->getString());
}

void ContainsEvaluator::getAllTNodesFrom(TNode* node, vector<TNode*> &result) {
    result.push_back(node);
    vector <TNode*> children = node->getChildren();
    for (vector<TNode*>::iterator it = children.begin();
        it != children.end();
        it++) {
        getAllTNodesFrom(*it, result);
    }
}

TType ContainsEvaluator::toTType(QNodeType type) {
    if (type == PROCEDURESYNONYM) {
        return PROCEDUREN;
    } else if (type == STMTLSTSYNONYM) {
        return STMTLSTN;
    } else if (type == ASSIGNSYNONYM) {
        return ASSIGNN;
    } else if (type == CALLSYNONYM) {
        return CALLN;
    } else if (type == WHILESYNONYM) {
        return WHILEN;
    } else if (type == IFSYNONYM) {
        return IFN;   
    }
}

int ContainsEvaluator::toInt(TNode* node) {
    if (node->getTType() == PROCEDUREN) {
        return pkb->getProcTable()->getProcIndex(node->getValue());
    } else if (node->getTType() == ASSIGNN ||
        node->getTType() == CALLN ||
        node->getTType() == WHILEN ||
        node->getTType() == IFN) {
        return node->getStmtLine();
    } else if (node->getTType() == STMTLSTN) {
        return node->getChildren()[0]->getStmtLine();
    } else {
        return (int) node;
    }
}

bool ContainsEvaluator::matchType(QNodeType qtype, TType ttype) {
    if (qtype == STMTSYNONYM || qtype == PROGLINESYNONYM) {
        return ttype == ASSIGNN ||
            ttype == IFN ||
            ttype == CALLN ||
            ttype == WHILEN;
    } else {
        return toTType(qtype) == ttype;
    }
}