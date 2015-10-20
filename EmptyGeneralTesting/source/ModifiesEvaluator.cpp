#include <ModifiesEvaluator.h>

ModifiesEvaluator::ModifiesEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool ModifiesEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getModifies()->isModifiesForStmt(left, right);
}

vector<int> ModifiesEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getModifies()->getModifiedByStmt(left);
}

vector<int> ModifiesEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getModifies()->getModifiesForStmt(right);
}

int ModifiesEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int ModifiesEvaluator::getConstRight(const QNode* const node) const {
    return pkb->getVarTable()->getVarIndex(node->getChildren()[1]->getString());
}

bool ModifiesEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[0]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool ModifiesEvaluator::checkRight(const QNode* const node, const int tested) const {
    return true;
}

vector <int> ModifiesEvaluator::getAllLeft(const QNode* const node, 
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

vector <int> ModifiesEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getVarTable()->getAllVarIndex();
}