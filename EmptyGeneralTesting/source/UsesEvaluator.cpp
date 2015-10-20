#include <UsesEvaluator.h>


UsesEvaluator::UsesEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool UsesEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getUses()->isUsesForStmt(left, right);
}

vector<int> UsesEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getUses()->getUsedByStmt(left);
}

vector<int> UsesEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getUses()->getUsesForStmt(right);
}

int UsesEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int UsesEvaluator::getConstRight(const QNode* const node) const {
    return pkb->getVarTable()->getVarIndex(node->getChildren()[1]->getString());
}

bool UsesEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return node->getChildren()[0]->getQType() == STMTSYNONYM ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool UsesEvaluator::checkRight(const QNode* const node, const int tested) const {
    return true;
}

vector <int> UsesEvaluator::getAllLeft(const QNode* const node, 
    const QueryResult &result) const {
    if (node->getChildren()[0]->getQType()== ANY) {
        return pkb->getAst()->getStmtLines(STMTN);
    }
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[0]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getAst()->getStmtLines(
        synonymToTType(node->getChildren()[0]->getQType()));
}

vector <int> UsesEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    if (node->getChildren()[1]->getQType()== ANY) {
        return pkb->getAst()->getStmtLines(STMTN);
    }
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getVarTable()->getAllVarIndex();
}