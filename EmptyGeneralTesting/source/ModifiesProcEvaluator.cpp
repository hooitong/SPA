#include <ModifiesProcEvaluator.h>

ModifiesProcEvaluator::ModifiesProcEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool ModifiesProcEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getModifies()->isModifiesForProc(left, right);
}

vector<int> ModifiesProcEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getModifies()->getModifiedByProc(left);
}

vector<int> ModifiesProcEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getModifies()->getModifiesForProc(right);
}

int ModifiesProcEvaluator::getConstLeft(const QNode* const node) const {
    return pkb->getProcTable()->getProcIndex(node->getChildren()[0]->getString());
}

int ModifiesProcEvaluator::getConstRight(const QNode* const node) const {
    return pkb->getVarTable()->getVarIndex(node->getChildren()[1]->getString());
}

bool ModifiesProcEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return true;
}

bool ModifiesProcEvaluator::checkRight(const QNode* const node, const int tested) const {
    return true;
}

vector <int> ModifiesProcEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[0]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getProcTable()->getAllProcIndex();
}

vector <int> ModifiesProcEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getVarTable()->getAllVarIndex();
}