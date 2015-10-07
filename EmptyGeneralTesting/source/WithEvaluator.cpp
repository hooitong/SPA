#include "WithEvaluator.h"
#include <cassert>

WithEvaluator::WithEvaluator(PKB* pkb) {
    this->pkb = pkb;
}

QueryResult WithEvaluator::evaluate(QNode* node) const {
    assert(node->getQType() == WITH);
    QNode* leftChild = node->getChildren()[0];
    QNode* rightChild = node->getChildren()[1];
    if (isConst(leftChild) && isConst(rightChild)) {
        return QueryResult(leftChild->getString() == rightChild->getString());
    } else if (!isConst(leftChild) && !isConst(rightChild)) {
        vector <pair<int,string> > possibleLeft = getAllOfType(leftChild);
        vector <pair<int,string> > possibleRight = getAllOfType(rightChild); 
        vector<pair<int,int> > possiblePairing;
        for (vector<pair<int,string> >::iterator itLeft = possibleLeft.begin();
            itLeft != possibleLeft.end();
            itLeft++) {
            for (vector<pair<int,string> >::iterator itRight = possibleRight.begin();
                itRight != possibleRight.end();
                itRight++) {
                if (itLeft->second == itRight->second) {
                    possiblePairing.push_back(
                        make_pair(itLeft->first, itRight->first));
                }
            }
        }
        return QueryResult(possiblePairing, 
            leftChild->getString(), 
            rightChild->getString());
    } else {
        if (isConst(leftChild)) {
            swap(leftChild, rightChild);
        }
        vector<pair<int, string> > possible = getAllOfType(leftChild);
        vector<int> result;
        for (vector<pair<int, string> >::iterator it = possible.begin();
            it != possible.end(); it++) {
            if (it->second == rightChild->getString()) {
                result.push_back(it->first);
            }
        }
        return QueryResult(result, leftChild->getString());
    }
}

vector<pair<int, string> > WithEvaluator::getAllOfType(QNode* node) const {
    vector <pair<int, string> > result;
    if (node->getQType() == PROCEDURESYNONYM) {
        vector <int> procedureIndexes = pkb->getProcTable()->getAllProcIndex();
        for (vector<int>::iterator it = procedureIndexes.begin();
            it != procedureIndexes.end(); it++) {
            result.push_back(make_pair(*it, pkb->getProcTable()->getProcName(*it)));
        }
    } else if (node->getQType() == VARIABLESYNONYM) {
        vector <int> varIndexes = pkb->getVarTable()->getAllVarIndex();
        for (vector<int>::iterator it = varIndexes.begin();
            it != varIndexes.end(); it++) {
            result.push_back(make_pair(*it, pkb->getVarTable()->getVarName(*it)));
        }
    } else if (node->getQType() == CALLSYNONYM && 
        node->getChildren()[0]->getString() == "procName") {
        vector <int> callIndexes = pkb->getAst() ->getStmtLines(CALLN);
        for (vector<int>::iterator it = callIndexes.begin();
            it != callIndexes.end(); it++) {
            TNode* node = pkb->getAst()->getTNode(*it);
            result.push_back(make_pair(*it, node->getValue()));
        }
    } else {
        vector <int> indexes = pkb->getAst()->getStmtLines(synonymToTType(node->getQType()));
        for (vector<int>::iterator it = indexes.begin();
            it != indexes.end(); it++) {
            ostringstream oss;
            oss << *it;
            result.push_back(make_pair(*it, oss.str()));
        }
    }
    return result;
}

TType WithEvaluator::synonymToTType(QNodeType type) const {
    if (type == WHILESYNONYM) {
        return WHILEN;
    } else if (type == ASSIGNSYNONYM) {
        return ASSIGNN;
    } else if (type == VARIABLESYNONYM) {
        return VARN;
    } else if (type == PROCEDURESYNONYM) {
        return PROCEDUREN;
    } else if (type == STMTSYNONYM) {
        return STMTN;
    } else if (type == PROGLINESYNONYM) {
	    return STMTN;
    } else if (type == CALLSYNONYM) {
        return CALLN;
    } else if (type == IFSYNONYM) {
        return IFN;
    }
}

bool WithEvaluator::isConst(QNode* node) const {
    return node->getQType() == CONST || node->getQType() == VAR;
}