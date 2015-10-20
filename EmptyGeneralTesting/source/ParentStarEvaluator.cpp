#include <ParentStarEvaluator.h>

ParentStarEvaluator::ParentStarEvaluator(PKB* pkb) : RelationEvaluator(pkb){}
bool ParentStarEvaluator::solveConstConst(const int left, const int right, const QueryResult& result) const
{
    return pkb->getParent()->isParentStar(left, right);
}

vector<int> ParentStarEvaluator::solveConstSyn(const int left, const QueryResult& result) const
{
    return pkb->getParent()->getChildOfStar(left);
}

vector<int> ParentStarEvaluator::solveSynConst(const int right, const QueryResult& result) const
{
    return pkb->getParent()->getParentStar(right);
}

int ParentStarEvaluator::getConstLeft(const QNode* const node) const {
    istringstream iss(node->getChildren()[0]->getString());
    int result;
    iss >> result;
    return result;
}

int ParentStarEvaluator::getConstRight(const QNode* const node) const {
    istringstream iss(node->getChildren()[1]->getString());
    int result;
    iss >> result;
    return result;
}

bool ParentStarEvaluator::checkLeft(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[0]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[0]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

bool ParentStarEvaluator::checkRight(const QNode* const node, const int tested) const {
    return synonymToTType(node->getChildren()[1]->getQType()) == STMTN ||
        synonymToTType(node->getChildren()[1]->getQType()) ==
        pkb->getAst()->getTNode(tested)->getTType();
}

vector <int> ParentStarEvaluator::getAllLeft(const QNode* const node, 
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

vector <int> ParentStarEvaluator::getAllRight(const QNode* const node, 
    const QueryResult &result) const {
    if (node->getChildren()[1]->getQType()== ANY) {
        return pkb->getAst()->getStmtLines(STMTN);
    }
    set<int> possibleValues = result.getPossibleValues(node->getChildren()[1]->getString());
    if (possibleValues.size() > 0) {
        return vector<int>(possibleValues.begin(), possibleValues.end());
    }
    return pkb->getAst()->getStmtLines(
        synonymToTType(node->getChildren()[1]->getQType()));
}