#include <ModifiesEvaluator.h>
#include <algorithm>

QueryResult ModifiesEvaluator::evaluate(QNode* node) {
    QNode* leftChild = node->getChildren()[0];
    QNode* rightChild = node->getChildren()[1];
    if (leftChild->getQType() == ANY && 
        rightChild->getQType() == ANY) {
        return evaluateAnyAny(node);
    } else if (leftChild->getQType() == ANY && 
        isSynonym(rightChild->getQType())) {
        return evaluateAnySyn(node);
    } else if (leftChild->getQType() == ANY &&
        rightChild->getQType() == VAR) {
        return evaluateAnyConst(node);
    } else if (isSynonym(leftChild->getQType()) &&
        rightChild->getQType() == ANY) {
        return evaluateSynAny(node);
    } else if (isSynonym(leftChild->getQType()) &&
        isSynonym(rightChild->getQType())) {
        return evaluateSynSyn(node);
    } else if (isSynonym(leftChild->getQType()) &&
        rightChild->getQType() == VAR) {
        return evaluateSynConst(node);
    } else if (leftChild->getQType() == CONST &&
        rightChild->getQType() == ANY) {
        return evaluateConstAny(node);
    } else if (leftChild->getQType() == CONST &&
        isSynonym(rightChild->getQType())) {
        return evaluateConstSyn(node);
    } else if (leftChild->getQType() == CONST &&
        rightChild->getQType() == VAR) {
        return evaluateConstConst(node);
    }
}

QueryResult ModifiesEvaluator::evaluateAnyAny(QNode* node) {
    Modifies* follows = pkb->getModifies();
    vector<STMTLINE> leftLines = pkb->getAst()->getStmtLines(TType::STMTN);
    for (vector<STMTLINE>::size_type i = 0; i < leftLines.size(); i++) {
        if (pkb->getModifies()->getModifiedByStmt(leftLines[i]).size() > 0) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult ModifiesEvaluator::evaluateAnyConst(QNode* node) {
    VARNAME rightName = node->getChildren()[1]->getString();
    VARINDEX rightConst = pkb->getVarTable()->getVarIndex(rightName);
    vector<STMTLINE> leftLines = pkb->getModifies()->getModifies(rightConst);
    return QueryResult(leftLines.size() > 0);
}

QueryResult ModifiesEvaluator::evaluateAnySyn(QNode* node) {
    string rightName = node->getChildren()[1]->getString();
    vector<VARINDEX> vars = pkb->getVarTable()->getAllVarIndex();
    vector<int> result;
    for (vector<VARINDEX>::size_type i = 0; i < vars.size(); i++) {
        vector <STMTLINE> leftLines = pkb->getModifies()->getModifies(vars[i]);
        if (leftLines.size() > 0) {
            result.push_back(vars[i]);
        }
    }
    return QueryResult(result, rightName);
}

QueryResult ModifiesEvaluator::evaluateConstAny(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    Modifies* modifies = pkb->getModifies();
    vector<int> rightLines = modifies->getModifiedByStmt(leftConst);
    return QueryResult(rightLines.size() > 0);
}

QueryResult ModifiesEvaluator::evaluateConstConst(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    VARNAME rightName = node->getChildren()[1]->getString();
    int rightConst = pkb->getVarTable()->getVarIndex(rightName);
    Modifies* modifies = pkb->getModifies();
    vector <int> possibleRight = modifies->getModifiedByStmt(leftConst);
    vector <int>::iterator location = find(possibleRight.begin(),
        possibleRight.end(),
        rightConst);
    return QueryResult(location != possibleRight.end());
}

QueryResult ModifiesEvaluator::evaluateConstSyn(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    vector<VARINDEX> rightVars = 
        pkb->getModifies()->getModifiedByStmt(leftConst);
    string rightSynonym = node->getChildren()[1]->getString();
    return QueryResult(rightVars, rightSynonym);
}

QueryResult ModifiesEvaluator::evaluateSynAny(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    vector <STMTLINE> lines = pkb->getAst()->getStmtLines(leftType);
    vector <STMTLINE> result;
    for (vector<STMTLINE>::size_type i = 0; i < lines.size(); i++) {
        vector<VARINDEX> rightVars = 
            pkb->getModifies()->getModifiedByStmt(lines[i]);
        if (rightVars.size() > 0) {
            result.push_back(lines[i]);
        }
    }
    return QueryResult(result, leftSynonym);
}

QueryResult ModifiesEvaluator::evaluateSynConst(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    VARNAME rightName = node->getChildren()[1]->getString();
    int rightConst = pkb->getVarTable()->getVarIndex(rightName);
    vector<int> leftLines = pkb->getModifies()->getModifies(rightConst);
    if (leftLines.size() > 0) {
        vector <int> resultVector;
        resultVector = filter(leftLines, leftType);
        return QueryResult(resultVector, leftSynonym);
    } else {
        return QueryResult(false);
    }
}

QueryResult ModifiesEvaluator::evaluateSynSyn(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    string rightSynonym = node->getChildren()[1]->getString();
    TType rightType = synonymToTType(node->getChildren()[1]->getQType());
    vector <STMTLINE> leftLines = pkb->getAst()->getStmtLines(leftType);
    vector<pair<STMTLINE, VARINDEX> > resultVector;
    for (vector<STMTLINE>::size_type i = 0; i < leftLines.size(); i++) {
        vector<VARINDEX> rightVars = pkb->getModifies()->getModifiedByStmt(leftLines[i]);
        for (vector<VARINDEX>::size_type j = 0; j < rightVars.size(); j++) {
            resultVector.push_back(make_pair(leftLines[i], rightVars[j]));
        }
    }
    return QueryResult(resultVector, leftSynonym, rightSynonym);
}