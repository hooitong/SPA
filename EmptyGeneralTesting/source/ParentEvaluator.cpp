#include <ParentEvaluator.h>

QueryResult ParentEvaluator::evaluate(QNode* node) {
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

QueryResult ParentEvaluator::evaluateAnyAny(QNode* node) {
    Follows* follows = pkb->getFollows();
    vector<STMTLINE> leftLines = pkb->getAst()->getStmtLines(TType::STMTN);
    for (vector<STMTLINE>::size_type i = 0; i < leftLines.size(); i++) {
        if (pkb->getParent()->getChildOf(leftLines[i]).size() > 0) {
            return QueryResult(true);
        }
    }
    return QueryResult(false);
}

QueryResult ParentEvaluator::evaluateAnyConst(QNode* node) {
    int rightConst = getInteger(node->getChildren()[1]);
    STMTLINE leftLine = 
        pkb->getParent()->getParent(rightConst);
    return leftLine >= 0;
}

QueryResult ParentEvaluator::evaluateAnySyn(QNode* node) {
    string synonymName = node->getChildren()[1]->getString();
    TType type = synonymToTType(node->getChildren()[1]->getQType());
    vector <STMTLINE> lines = pkb->getAst()->getStmtLines(type);
    vector <STMTLINE> result;
    for (vector<STMTLINE>::size_type i = 0; i < lines.size(); i++) {
        int leftLine = pkb->getParent()->getParent(lines[i]);
        if (leftLine >= 0) {
            result.push_back(lines[i]);
        }
    }
    return QueryResult(result, synonymName);
}

QueryResult ParentEvaluator::evaluateConstAny(QNode* node) {
    int leftConst = getInteger(node->getChildren()[1]);
    vector<int> rightLines = pkb->getParent()->getChildOf(leftConst);
    return QueryResult(rightLines.size() > 0);
}

QueryResult ParentEvaluator::evaluateConstConst(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    int rightConst = getInteger(node->getChildren()[1]);
    return QueryResult(pkb->getParent()->isParent(leftConst, rightConst));
}

QueryResult ParentEvaluator::evaluateConstSyn(QNode* node) {
    int leftConst = getInteger(node->getChildren()[0]);
    string rightSynonym = node->getChildren()[1]->getString();
    vector<int> result = pkb->getParent()->getChildOf(leftConst);
    if (result.size() > 0) {
        return QueryResult(result, rightSynonym);
    } else {
        return QueryResult(false);
    }
}

QueryResult ParentEvaluator::evaluateSynAny(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    vector <STMTLINE> lines = pkb->getAst()->getStmtLines(leftType);
    vector <STMTLINE> result;
    for (vector<STMTLINE>::size_type i = 0; i < lines.size(); i++) {
        vector<int> rightLines = pkb->getParent()->getChildOf(lines[i]);
        if (rightLines.size() > 0) {
            result.push_back(lines[i]);
        }
    }
    return QueryResult(result, leftSynonym);
}

QueryResult ParentEvaluator::evaluateSynConst(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    int rightConst = getInteger(node->getChildren()[1]);
    int leftLine = pkb->getParent()->getParent(rightConst);
    if (leftLine >= 0) {
        vector <int> resultVector(1, leftLine);
        return QueryResult(resultVector, leftSynonym);
    } else {
        return QueryResult(false);
    }
}

QueryResult ParentEvaluator::evaluateSynSyn(QNode* node) {
    string leftSynonym = node->getChildren()[0]->getString();
    TType leftType = synonymToTType(node->getChildren()[0]->getQType());
    string rightSynonym = node->getChildren()[1]->getString();
    TType rightType = synonymToTType(node->getChildren()[1]->getQType());
    vector <STMTLINE> leftLines = pkb->getAst()->getStmtLines(leftType);
    vector<pair<STMTLINE, STMTLINE> > resultVector;
    for (vector<STMTLINE>::size_type i = 0; i < leftLines.size(); i++) {
        vector<STMTLINE> rightLines = 
            pkb->getParent()->getChildOf(leftLines[i]);
        for (vector<STMTLINE>::size_type j = 0; j < rightLines.size(); j++) {
            if (pkb->getAst()->getTNode(rightLines[j])->getTType() == rightType) {
                resultVector.push_back(make_pair(leftLines[i], rightLines[j]));
            }
        }
    }
    return QueryResult(resultVector, leftSynonym, rightSynonym);
}