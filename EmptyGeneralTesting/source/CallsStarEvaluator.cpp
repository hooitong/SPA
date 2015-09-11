#include <CallsStarEvaluator.h>

QueryResult CallsStarEvaluator::evaluate(QNode* node) {
    QNode* leftChild = node->getChildren()[0];
    QNode* rightChild = node->getChildren()[1];
    if (leftChild->getQType() == ANY && 
        rightChild->getQType() == ANY) {
        return evaluateAnyAny(node);
    } else if (leftChild->getQType() == ANY && 
        isSynonym(rightChild->getQType())) {
        return evaluateAnySyn(node);
    } else if (leftChild->getQType() == ANY &&
        rightChild->getQType() == CONST) {
        return evaluateAnyConst(node);
    } else if (isSynonym(leftChild->getQType()) &&
        rightChild->getQType() == ANY) {
        return evaluateSynAny(node);
    } else if (isSynonym(leftChild->getQType()) &&
        isSynonym(rightChild->getQType())) {
        return evaluateSynSyn(node);
    } else if (isSynonym(leftChild->getQType()) &&
        rightChild->getQType() == CONST) {
        return evaluateSynConst(node);
    } else if (leftChild->getQType() == CONST &&
        rightChild->getQType() == ANY) {
        return evaluateConstAny(node);
    } else if (leftChild->getQType() == CONST &&
        isSynonym(rightChild->getQType())) {
        return evaluateConstSyn(node);
    } else if (leftChild->getQType() == CONST &&
        rightChild->getQType() == CONST) {
        return evaluateConstConst(node);
    }
}

QueryResult CallsStarEvaluator::evaluateAnyAny(QNode* node) {
    Calls* calls = pkb->getCalls();
    vector<PROCINDEX> leftProcs = pkb->getProcTable()->getAllProcIndex();
    for (vector<PROCINDEX>::size_type i = 0; i < leftProcs.size(); i++) {
        if (pkb->getCalls()->getCalledByStar(leftProcs[i]).size() > 0) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult CallsStarEvaluator::evaluateAnyConst(QNode* node) {
    PROCNAME rightName = node->getChildren()[1]->getString();
    PROCINDEX rightConst = pkb->getProcTable()->getProcIndex(rightName);
    Calls* calls = pkb->getCalls();
    vector<PROCINDEX> leftResult = calls->getCallsToStar(rightConst);
    return QueryResult(leftResult.size() > 0);
}

QueryResult CallsStarEvaluator::evaluateAnySyn(QNode* node) {
    string synonymName = node->getChildren()[1]->getString();
    vector <PROCINDEX> rightProcs = pkb->getProcTable()->getAllProcIndex();
    vector <PROCINDEX> result;
    for (vector<PROCINDEX>::size_type i = 0; i < rightProcs.size(); i++) {
        vector<PROCINDEX> leftProcs = pkb->getCalls()->getCallsToStar(rightProcs[i]);
        if (leftProcs.size() > 0) {
            result.push_back(rightProcs[i]);
        }
    }
    return QueryResult(result, synonymName);
}

QueryResult CallsStarEvaluator::evaluateConstAny(QNode* node) {
    PROCNAME leftName = node->getChildren()[0]->getString();
    PROCINDEX leftConst = pkb->getProcTable()->getProcIndex(leftName);
    vector<PROCINDEX> result = pkb->getCalls()->getCalledByStar(leftConst);
    return QueryResult(result.size() > 0);
}

QueryResult CallsStarEvaluator::evaluateConstConst(QNode* node) {
    PROCNAME leftName = node->getChildren()[0]->getString();
    PROCNAME rightName = node->getChildren()[1]->getString();
    PROCINDEX leftConst = pkb->getProcTable()->getProcIndex(leftName);
    PROCINDEX rightConst = pkb->getProcTable()->getProcIndex(rightName);
    Calls* calls = pkb->getCalls();
    return QueryResult(calls->isCallStar(leftConst, rightConst));
}

QueryResult CallsStarEvaluator::evaluateConstSyn(QNode* node) {
    PROCNAME leftName = node->getChildren()[0]->getString();
    PROCINDEX leftConst = pkb->getProcTable()->getProcIndex(leftName);
    string rightSynonym = node->getChildren()[1]->getString();
    Calls* calls = pkb->getCalls();
    vector<PROCINDEX> result = calls->getCalledByStar(leftConst);
    return QueryResult(result, rightSynonym);
}

QueryResult CallsStarEvaluator::evaluateSynAny(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    vector <PROCINDEX> procs = pkb->getProcTable()->getAllProcIndex();
    vector <PROCINDEX> result;
    for (vector<STMTLINE>::size_type i = 0; i < procs.size(); i++) {
        vector<PROCINDEX> rightIndex = pkb->getCalls()->getCalledByStar(procs[i]);
        if (rightIndex.size() > 0) {
            result.push_back(procs[i]);
        }
    }
    return QueryResult(result, leftSynonym);
}

QueryResult CallsStarEvaluator::evaluateSynConst(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    PROCNAME rightName = node->getChildren()[1]->getString();
    PROCINDEX rightConst = pkb->getProcTable()->getProcIndex(rightName);
    vector<PROCINDEX> leftConst = pkb->getCalls()->getCallsToStar(rightConst);
    return QueryResult(leftConst, leftSynonym);
}

QueryResult CallsStarEvaluator::evaluateSynSyn(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    string rightSynonym = node->getChildren()[1]->getString();
    vector <PROCINDEX> leftProcs = pkb->getProcTable()->getAllProcIndex();
    vector<pair<PROCINDEX, PROCINDEX> > resultVector;
    for (vector<PROCINDEX>::size_type i = 0; i < leftProcs.size(); i++) {
        vector<PROCINDEX> rightProcs = pkb->getCalls()->getCalledByStar(leftProcs[i]);
        for (vector<PROCINDEX>::size_type j = 0; j < rightProcs.size(); j++) {
            resultVector.push_back(make_pair(leftProcs[i], rightProcs[j]));
        }
    }
    return QueryResult(resultVector, leftSynonym, rightSynonym);
}