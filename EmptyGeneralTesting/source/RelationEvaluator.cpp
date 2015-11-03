#include <RelationEvaluator.h>
#include <sstream>
#include <iostream>

RelationEvaluator::RelationEvaluator(PKB* pkb) {
    this->pkb = pkb;
}
int RelationEvaluator::getInteger(QNode* node) const {
    std::istringstream iss(node->getString());
    int result;
    iss >> result;
    return result;
}

bool RelationEvaluator::isSynonym(QNodeType type) const {
    return type == WHILESYNONYM ||
           type == ASSIGNSYNONYM ||
           type == VARIABLESYNONYM ||
           type == PROCEDURESYNONYM ||
           type == CONSTSYNONYM ||
           type == PROGLINESYNONYM ||
           type == IFSYNONYM ||
           type == STMTSYNONYM ||
           type == CALLSYNONYM;
}

bool RelationEvaluator::isConst(QNodeType type) const {
    return type == CONST ||
           type == VAR;
}



TType RelationEvaluator::synonymToTType(QNodeType type) const {
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

vector<STMTLINE> RelationEvaluator::filter(vector<STMTLINE> original, TType type) const {
    if (type == STMTN) {
        return original;
    }
    vector<STMTLINE> result;
    for (vector<STMTLINE>::size_type i = 0; i < original.size(); i++) {
        if (pkb->getAst()->getTNode(original[i])->getTType() == type) {
            result.push_back(original[i]);
        }
    }
    return result;
}

void RelationEvaluator::updateAnyAny(const QNode* const node, 
    QueryResult& result) const
{
    vector <int> possibleLeft = getAllLeft(node, result);
    for (vector<int>::size_type i = 0; i < possibleLeft.size(); i++) {
        int leftConst = possibleLeft[i];
        vector <int> possibleRight = solveConstSyn(leftConst, result);
        if (possibleRight.size() > 0) {
            return;
        }
    }
    result = result.merge(QueryResult(false));
}

void RelationEvaluator::updateAnyConst(const QNode* const node,
    QueryResult& result) const
{
    int right = getConstRight(node);
    vector <int> possibleLeft = solveSynConst(right, result);
    if (possibleLeft.size() == 0) {
        result = result.merge(QueryResult(false));
    }
}

void RelationEvaluator::updateAnySyn(const QNode* const node,
    QueryResult& result) const
{
    vector <int> possibleRight = getAllRight(node, result);
    vector <int> newResult;
    for (vector<int>::size_type i = 0; i < possibleRight.size(); i++) {
        vector <int> possibleLeft = solveSynConst(possibleRight[i], result);
        if (possibleLeft.size() > 0) {
            newResult.push_back(possibleRight[i]);
        }
    }
    string rightSynonym = node->getChildren()[1]->getString();
    result = result.merge(QueryResult(newResult, rightSynonym));
}

void RelationEvaluator::updateConstAny(const QNode* const node,
    QueryResult &result) const
{
    int leftConst = getConstLeft(node);
    vector <int> possibleRight = solveConstSyn(leftConst, result);
    if (possibleRight.size() == 0) {
        result = result.merge(QueryResult(false));
    }
}

void RelationEvaluator::updateConstConst(const QNode* const node,
    QueryResult &result) const
{
    int leftConst = getConstLeft(node);
    int rightConst = getConstRight(node);
    bool newResult = solveConstConst(leftConst, rightConst, result);
    result = result.merge(QueryResult(newResult));
}

void RelationEvaluator::updateConstSyn(const QNode* const node,
    QueryResult &result) const
{
    int leftConst = getConstLeft(node);
    vector <int> possibleRight = solveConstSyn(leftConst, result);
    vector <int> newResult;
    for (vector<int>::iterator it = possibleRight.begin(); 
        it != possibleRight.end(); 
        it++) {
        if (checkRight(node, *it)) {
            newResult.push_back(*it);
        }
    }

    string rightSynonym = node->getChildren()[1]->getString();
    result = result.merge(QueryResult(newResult, rightSynonym));
}

void RelationEvaluator::updateSynAny(const QNode* const node,
    QueryResult &result) const
{
    vector <int> possibleLeft = getAllLeft(node, result);
    vector <int> newResult;
    for (vector<int>::iterator it = possibleLeft.begin();
        it != possibleLeft.end(); it++) {
        vector <int> possibleRight = solveConstSyn(*it, result);
        if (possibleRight.size() > 0) {
            newResult.push_back(*it);
        }
    }
    string synonymLeft = node->getChildren()[0]->getString();
    result = result.merge(QueryResult(newResult, synonymLeft));
}

void RelationEvaluator::updateSynConst(const QNode* const node,
    QueryResult &result) const
{
    int rightConst = getConstRight(node);
    vector <int> possibleLeft = solveSynConst(rightConst, result);
    vector <int> newResult;
    for (vector<int>::iterator it = possibleLeft.begin();
        it != possibleLeft.end(); it++) {
        if (checkLeft(node, *it)) {
            newResult.push_back(*it);
        }
    }
    string leftSynonym = node->getChildren()[0]->getString();
    result = result.merge(QueryResult(newResult, leftSynonym));
}

void RelationEvaluator::updateSynSyn(const QNode* const node,
    QueryResult &result) const
{
    vector <int> possibleLeft = getAllLeft(node, result);
    vector <int> possibleRight = getAllRight(node, result);
    string synonymLeft = node->getChildren()[0]->getString();
    string synonymRight = node->getChildren()[1]->getString();
    if (possibleLeft.size() < possibleRight.size()) {
        vector <pair<int,int> > newResult;
        for (vector<int>::iterator it = possibleLeft.begin();
            it != possibleLeft.end(); 
            it++) {
            vector <int> rightResult = solveConstSyn(*it, result);
            for (vector<int>::iterator itRight = rightResult.begin();
                itRight != rightResult.end();
                itRight++) {
                    if (checkRight(node, *itRight)) {
                        newResult.push_back(make_pair(*it, *itRight));
                    }
            }
        }
        result = result.merge(QueryResult(newResult, synonymLeft, synonymRight));
    } else {
        vector <pair<int,int> > newResult;
        for (vector<int>::iterator it = possibleRight.begin();
            it != possibleRight.end(); 
            it++) {
            vector <int> leftResult = solveSynConst(*it, result);
            for (vector<int>::iterator itLeft = leftResult.begin();
                itLeft != leftResult.end();
                itLeft++) {
                    if (checkLeft(node, *itLeft)) {
                        newResult.push_back(make_pair(*itLeft, *it));
                    }
            }
        }
        result = result.merge(QueryResult(newResult, synonymLeft, synonymRight));
    }
}

void RelationEvaluator::updateResult(const QNode* const &node, QueryResult &result) {
    if (result.getSolutionsSize() == 0) {
        return;
    }
    if (node->getChildren()[0]->getQType() == ANY && 
        node->getChildren()[1]->getQType() == ANY) {
        updateAnyAny(node, result);
    } else if (node->getChildren()[0]->getQType() == ANY && 
        isConst(node->getChildren()[1]->getQType())) {
        updateAnyConst(node, result);
    } else if (node->getChildren()[0]->getQType() == ANY &&
        isSynonym(node->getChildren()[1]->getQType())) {
        updateAnySyn(node, result);
    } else if (isConst(node->getChildren()[0]->getQType()) &&
        node->getChildren()[1]->getQType() == ANY) {
        updateConstAny(node, result);
    } else if (isConst(node->getChildren()[0]->getQType()) &&
        isConst(node->getChildren()[1]->getQType())) {
        updateConstConst(node, result);
    } else if (isConst(node->getChildren()[0]->getQType()) &&
        isSynonym(node->getChildren()[1]->getQType())) {
        updateConstSyn(node, result);
    } else if (isSynonym(node->getChildren()[0]->getQType()) &&
        node->getChildren()[1]->getQType() == ANY) {
        updateSynAny(node, result);
    } else if (isSynonym(node->getChildren()[0]->getQType()) &&
        isConst(node->getChildren()[1]->getQType())) {
        updateSynConst(node, result);
    } else if (isSynonym(node->getChildren()[0]->getQType()) &&
        isSynonym(node->getChildren()[1]->getQType())) {
        updateSynSyn(node, result);
    }
}

QueryResult RelationEvaluator::evaluate(QNode* node) {
    cout << node->getQType() << endl;
    QueryResult result(true);
    updateResult(node, result);
    return result;
}