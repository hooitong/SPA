#include <CallsEvaluator.h>

CallsEvaluator::CallsEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool CallsEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getCalls()->isCall(left, right);
}

vector<int> CallsEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getCalls()->getCalledBy(left);
}

vector<int> CallsEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getCalls()->getCallsTo(right);
}

int CallsEvaluator::getConstLeft(const QNode* const node) const {
    return pkb->getProcTable()->getProcIndex(node->getChildren()[0]->getString());
}

int CallsEvaluator::getConstRight(const QNode* const node) const {
    return pkb->getProcTable()->getProcIndex(node->getChildren()[1]->getString());
}

bool CallsEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return true;
}

bool CallsEvaluator::checkRight(const QNode* const node, const int tested) const {
    return true;
}

vector <int> CallsEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[0]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getProcTable()->getAllProcIndex();
}

vector <int> CallsEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getProcTable()->getAllProcIndex();
}