#include <FollowsEvaluator.h>

QueryResult FollowsEvaluator::evaluate(QNode* node) {
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

QueryResult FollowsEvaluator::evaluateAnyAny(QNode* node) {
    Follows* follows = pkb->getFollows();
    vector<STMTLINE> leftLines = pkb->getAst()->getStmtLines(TType::STMTN);
    for (vector<STMTLINE>::size_type i = 0; i < leftLines.size(); i++) {
        if (pkb->getFollows()->getFollowedBy(leftLines[i]) >= 0) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult FollowsEvaluator::evaluateAnyConst(QNode* node) {
    int rightConst = getInteger(node->getChildren()[1]);
    Follows* follows = pkb->getFollows();
    int leftLine = follows->getFollowsFrom(rightConst);
    return QueryResult(leftLine >= 0);
}

QueryResult FollowsEvaluator::evaluateAnySyn(QNode* node) {
    string synonymName = node->getChildren()[1]->getString();
    TType type = synonymToTType(node->getChildren()[1]->getQType());
    vector <STMTLINE> lines = pkb->getAst()->getStmtLines(type);
    vector <STMTLINE> result;
    for (vector<STMTLINE>::size_type i = 0; i < lines.size(); i++) {
        int leftLine = pkb->getFollows()->getFollowsFrom(lines[i]);
        if (leftLine >= 0) {
            result.push_back(lines[i]);
        }
    }
    return QueryResult(result, synonymName);
}

QueryResult FollowsEvaluator::evaluateConstAny(QNode* node) {
    int leftConst = getInteger(node->getChildren()[1]);
    Follows* follows = pkb->getFollows();
    int rightLine = follows->getFollowedBy(leftConst);
    return QueryResult(rightLine >= 0);
}

QueryResult FollowsEvaluator::evaluateConstConst(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    int rightConst = getInteger(node->getChildren()[1]);
    Follows* follows = pkb->getFollows();
    return QueryResult(follows->isFollows(leftConst, rightConst));
}

QueryResult FollowsEvaluator::evaluateConstSyn(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    TType type = synonymToTType(node->getChildren()[1]->getQType());
    string rightSynonym = node->getChildren()[1]->getString();
    Follows* follows = pkb->getFollows();
    int result = follows->getFollowedBy(leftConst);
    if (result >= 0) {
        vector <int> resultVector(1, result);
        resultVector = filter(resultVector, type);
        return QueryResult(resultVector, rightSynonym);
    } else {
        return QueryResult(false);
    }
}

QueryResult FollowsEvaluator::evaluateSynAny(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    vector <STMTLINE> lines = pkb->getAst()->getStmtLines(leftType);
    vector <STMTLINE> result;
    for (vector<STMTLINE>::size_type i = 0; i < lines.size(); i++) {
        int rightLine = pkb->getFollows()->getFollowedBy(lines[i]);
        if (rightLine >= 0) {
            result.push_back(lines[i]);
        }
    }
    return QueryResult(result, leftSynonym);
}

QueryResult FollowsEvaluator::evaluateSynConst(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    int rightConst = getInteger(node->getChildren()[1]);
    int leftLine = pkb->getFollows()->getFollowsFrom(rightConst);
    if (leftLine >= 0) {
        vector<int> resultVector(1, leftLine);
        resultVector = filter(resultVector, leftType);
        return QueryResult(resultVector, leftSynonym);
    } else {
        return QueryResult(false);
    }
}

QueryResult FollowsEvaluator::evaluateSynSyn(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    string rightSynonym = node->getChildren()[1]->getString();
    TType rightType = synonymToTType(node->getChildren()[1]->getQType());
    vector <STMTLINE> leftLines = pkb->getAst()->getStmtLines(leftType);
    vector<pair<STMTLINE, STMTLINE> > resultVector;
    for (vector<STMTLINE>::size_type i = 0; i < leftLines.size(); i++) {
        STMTLINE rightLine = pkb->getFollows()->getFollowedBy(leftLines[i]);
        if (rightLine >= 0 && (rightType == STMTN ||
            pkb->getAst()->getTNode(rightLine)->getTType() == rightType)) {
            resultVector.push_back(make_pair(leftLines[i], rightLine));
        }
    }
    return QueryResult(resultVector, leftSynonym, rightSynonym);
}