#include "UsesProcEvaluator.h"


UsesProcEvaluator::UsesProcEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool UsesProcEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getUses()->isUsesForProc(left, right);
}

vector<int> UsesProcEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getUses()->getUsedByProc(left);
}

vector<int> UsesProcEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getUses()->getUsesForProc(right);
}

int UsesProcEvaluator::getConstLeft(const QNode* const node) const {
    return pkb->getProcTable()->getProcIndex(node->getChildren()[0]->getString());
}

int UsesProcEvaluator::getConstRight(const QNode* const node) const {
    return pkb->getVarTable()->getVarIndex(node->getChildren()[1]->getString());
}

bool UsesProcEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return true;
}

bool UsesProcEvaluator::checkRight(const QNode* const node, const int tested) const {
    return true;
}

vector <int> UsesProcEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[0]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getProcTable()->getAllProcIndex();
}

vector <int> UsesProcEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getVarTable()->getAllVarIndex();
}