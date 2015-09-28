#include "WithEvaluator.h"
#include <cassert>

WithEvaluator::WithEvaluator(PKB* pkb) {
    this->pkb = pkb;
}

QueryResult WithEvaluator::evaluate(QNode* node) {
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

vector<pair<int, string> > WithEvaluator::getAllOfType(QNode* node) {
    vector <pair<int, string> > result;
    if (node->getQType() == PROCEDURESYNONYM) {
        vector <int> procedureIndexes = pkb->getProcTable()->getAllProcIndex();
        for (vector<int>::iterator it = procedureIndexes.begin();
            it != procedureIndexes.end(); it++) {
            result.push_back(make_pair(*it, pkb->getProcTable()->getProcName(*it)));
        }
    }
    return result;
}

bool WithEvaluator::isConst(QNode* node) {
    return node->getQType() == CONST || node->getQType() == VAR;
}