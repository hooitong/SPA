#include "ContainsStarEvaluator.h"
#include <sstream>
#include <iostream>

ContainsStarEvaluator::ContainsStarEvaluator(PKB* pkb) {
    this->pkb = pkb;
}

QueryResult ContainsStarEvaluator::solveConstConst(QNode* node) {
    istringstream leftss(node->getChildren()[0]->getString());
    istringstream rightss(node->getChildren()[1]->getString());
    int leftNode;
    int rightNode;
    leftss >> leftNode;
    rightss >> rightNode;
    TNode* leftTNode = pkb->getAst()->getTNode(leftNode);
    vector <TNode*> subtree;
    getAllTNodesFrom(leftTNode, subtree);
    for (vector<TNode*>::iterator it = subtree.begin();
        it != subtree.end(); it++) {

        if ((*it)->getStmtLine() == rightNode && (*it)->getStmtLine() != leftNode) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult ContainsStarEvaluator::solveConstSyn(QNode* node) {
    istringstream leftss(node->getChildren()[0]->getString());
    int leftStmt;
    leftss >> leftStmt;
    TNode* leftTNode = pkb->getAst()->getTNode(leftStmt);
    vector <TNode*> subtree;
    getAllTNodesFrom(leftTNode, subtree);
    vector <int> result;
    for (vector<TNode*>::iterator it = subtree.begin();
        it != subtree.end(); it++) {
        if ((*it) != leftTNode && matchType(node->getChildren()[1]->getQType(), (*it)->getTType())) {
            result.push_back(toInt(*it));
        }
    }
    return QueryResult(result, node->getChildren()[1]->getString());
}

QueryResult ContainsStarEvaluator::solveSynConst(QNode* node) {
    istringstream rightss(node->getChildren()[1]->getString());
    int rightStmt;
    rightss >> rightStmt;
    TNode* rightNode = pkb->getAst()->getTNode(rightStmt);
    TNode* currentNode = rightNode->getParentNode();
    vector <int> result;
    while (currentNode->getTType() != EMPTYN) {
        cout << currentNode << endl;
        if (currentNode != NULL && matchType(node->getChildren()[0]->getQType(), currentNode->getTType())) {
            result.push_back(toInt(currentNode));   
        }
        currentNode = currentNode->getParentNode();
    }
    return QueryResult(result, node->getChildren()[0]->getString());
}

QueryResult ContainsStarEvaluator::solveSynSyn(QNode* node) {
    vector <TNode*> nodes;
    vector <int> progIndex = pkb->getProcTable()->getAllProcIndex();

    for (vector<int>::iterator it = progIndex.begin(); it != progIndex.end(); it++) {
        getAllTNodesFrom(pkb->getAst()->getProcTNodeByIndex(*it), nodes);
    }
    vector <pair<int,int> > results;
    for (vector<TNode*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        if (matchType(node->getChildren()[0]->getQType(), (*it)->getTType())) {
            vector <TNode*> children;
            getAllTNodesFrom(*it, children);
            for (vector<TNode*>::iterator it2 = children.begin(); it2 != children.end(); it2++) {
                if ((*it2) != (*it) && matchType(node->getChildren()[1]->getQType(), (*it2)->getTType())) {
                    results.push_back(make_pair(toInt(*it), toInt(*it2)));
                }
            }
        }
    }
    return QueryResult(results, node->getChildren()[0]->getString(), node->getChildren()[1]->getString());
}

void ContainsStarEvaluator::getAllTNodesFrom(TNode* node, vector<TNode*> &result) {
    result.push_back(node);
    vector <TNode*> children = node->getChildren();
    for (vector<TNode*>::iterator it = children.begin();
        it != children.end();
        it++) {
        getAllTNodesFrom(*it, result);
    }
}

TType ContainsStarEvaluator::toTType(QNodeType type) {
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
    } else if (type == CONSTSYNONYM) {
        return CONSTN;
    } else if (type == VARIABLESYNONYM) {
       return VARN;
    } else if (type == QPLUS) {
        return PLUSN;
    } else if (type == QTIMES) {
        return TIMESN;
    } else if (type == QMINUS) {
        return MINUSN;
    }
}

int ContainsStarEvaluator::toInt(TNode* node) {
    if (node->getTType() == PROCEDUREN) {
        return pkb->getProcTable()->getProcIndex(node->getValue());
    } else if (node->getTType() == ASSIGNN ||
        node->getTType() == CALLN ||
        node->getTType() == WHILEN ||
        node->getTType() == IFN) {
        return node->getStmtLine();
    } else if (node->getTType() == STMTLSTN) {
        return node->getChildren()[0]->getStmtLine();
    } else if (node->getTType() == CONSTN) {
        istringstream iss(node->getValue());
        int result;
        iss >> result;
        return result;
    } else if (node->getTType() == VARN) {
        return pkb->getVarTable()->getVarIndex(node->getValue());
    } else {
        return (int) node;
    }
}

bool ContainsStarEvaluator::matchType(QNodeType qtype, TType ttype) {
    if (qtype == STMTSYNONYM || qtype == PROGLINESYNONYM) {
        return ttype == ASSIGNN ||
            ttype == IFN ||
            ttype == CALLN ||
            ttype == WHILEN;
    } else {
        return toTType(qtype) == ttype;
    }
}

QueryResult ContainsStarEvaluator::evaluate(QNode* node) {
    cout << "TEST" << endl;
    if (node->getChildren()[0]->getQType() == CONST || node->getChildren()[0]->getQType() == VAR) {
        if (node->getChildren()[1]->getQType() == CONST || node->getChildren()[1]->getQType() == VAR) {
            return solveConstConst(node);
        } else {
            return solveConstSyn(node);
        }
    } else {
        if (node->getChildren()[1]->getQType() == CONST || node->getChildren()[1]->getQType() == VAR) {
            return solveSynConst(node);
        } else {
            return solveSynSyn(node);
        }
    }
}   