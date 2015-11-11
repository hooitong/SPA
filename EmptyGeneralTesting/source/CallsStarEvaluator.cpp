#include "CallsStarEvaluator.h"

CallsStarEvaluator::CallsStarEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool CallsStarEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getCalls()->isCallStar(left, right);
}

vector<int> CallsStarEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getCalls()->getCalledByStar(left);
}

vector<int> CallsStarEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getCalls()->getCallsToStar(right);
}

int CallsStarEvaluator::getConstLeft(const QNode* const node) const {
    return pkb->getProcTable()->getProcIndex(node->getChildren()[0]->getString());
}

int CallsStarEvaluator::getConstRight(const QNode* const node) const {
    return pkb->getProcTable()->getProcIndex(node->getChildren()[1]->getString());
}

bool CallsStarEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return true;
}

bool CallsStarEvaluator::checkRight(const QNode* const node, const int tested) const {
    return true;
}

vector <int> CallsStarEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[0]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getProcTable()->getAllProcIndex();
}

vector <int> CallsStarEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getProcTable()->getAllProcIndex();
}