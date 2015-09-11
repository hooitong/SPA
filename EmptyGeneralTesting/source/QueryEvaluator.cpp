#include "QueryEvaluator.h"
#include "FollowsEvaluator.h"
#include "FollowsStarEvaluator.h"
#include "ParentEvaluator.h"
#include "ParentStarEvaluator.h"
#include "ModifiesEvaluator.h"
#include "CallsEvaluator.h"
#include "CallsStarEvaluator.h"
#include "UsesEvaluator.h"

QueryEvaluator::QueryEvaluator(PKB* pkb) {
    pkbInstance = pkb;
}

std::list<string> QueryEvaluator::evaluate(QueryTree* tree) {
    if (tree == NULL) {
        return std::list<string>();
    }
    QueryResult result = evaluate(tree->getRoot());


    vector <string> resultSynonym;
    map <string, TType> synonymMap;
    vector<QueryResult> resultFilters;

    vector <QNode*> children = tree->getRoot()->getChildren();
    for (int i = 0; i < (int) children.size(); i++) {
        if (children[i]->getQType() == RESULTLIST) {
            resultSynonym = getResultSynonyms(children[i]);
            synonymMap = getSynonymMap(children[i]);
            resultFilters = getResultFilters(children[i]);
        }
    }

    for (int i = 0; i < (int) resultFilters.size(); i++) {
        result = result.merge(resultFilters[i]);
    }

    result = result.filter(resultSynonym);

    vector <vector<int> > solutions = result.getResult();

    std::list<string> resultList;
    for (int i = 0; i < (int)solutions.size(); i++) {
        ostringstream oss;
        for (int j = 0; j < (int) solutions[i].size(); j++) {
            if (j > 0) {
                oss << " ";
            }

            if (synonymMap[resultSynonym[j]] == VARN) {
                oss << pkbInstance->getVarTable()->getVarName(solutions[i][j]);
            } else if (synonymMap[resultSynonym[j]] == PROCEDUREN) {
                oss << pkbInstance->getProcTable()->getProcName(solutions[i][j]);
            } else {
                oss << solutions[i][j];
            }
        }
        resultList.push_back(oss.str());
    }

    return resultList;
}

vector<QueryResult> QueryEvaluator::getResultFilters(QNode* node) {
    assert(node->getQType() == RESULTLIST);

    vector <QNode*> children = node->getChildren();
    vector <QueryResult> resultList;
    for (int i = 0; i < (int) children.size(); i++) {
        vector <int> result;
        if (children[i]->getQType() == WHILESYNONYM) {
            result = pkbInstance->getAst()->getStmtLines(WHILEN);
        } else if (children[i]->getQType() == STMTSYNONYM) {
            result = pkbInstance->getAst()->getStmtLines(STMTN);
        } else if (children[i]->getQType() == ASSIGNSYNONYM) {
            result = pkbInstance->getAst()->getStmtLines(ASSIGNN);
        } else if (children[i]->getQType() == PROCEDURESYNONYM) {
            result = pkbInstance->getProcTable()->getAllProcIndex();
        } else if (children[i]->getQType() == VARIABLESYNONYM) {
            result = pkbInstance->getVarTable()->getAllVarIndex();
        } else if (children[i]->getQType() == PROGLINESYNONYM) {
            result = pkbInstance->getAst()->getStmtLines(STMTN);
        }
        vector<string> synonyms;
        resultList.push_back(QueryResult(result, children[i]->getString()));
    }
    return resultList;
}

vector<STMTLINE> QueryEvaluator::filter(vector<STMTLINE> original, TType type) {
    if (type == STMTN) {
        return original;
    }
    vector <STMTLINE> result;
    for (vector<STMTLINE>::iterator it = original.begin();
            it != original.end(); it++) {
        TType lineType = pkbInstance->getAst()->getTNode(*it)->getTType();
        if (lineType == type) {
            result.push_back(*it);
        }
    }
    return result;
}

vector<string> QueryEvaluator::getResultSynonyms(QNode* node) {
    assert(node->getQType() == RESULTLIST);
    vector <string> result;
    vector<QNode*> children = node->getChildren();
    for (int i = 0; i < (int) children.size(); i++) {
        result.push_back(children[i]->getString());
    }
    return result;
}

map<string, TType> QueryEvaluator::getSynonymMap(QNode* node) {
    assert(node->getQType() == RESULTLIST);
    map <string, TType> synonymMap;
    vector<QNode*> children = node->getChildren();
    for (int i = 0; i < (int) children.size(); i++) {
        synonymMap[children[i]->getString()] =
            synonymToTType(children[i]->getQType());
    }

    return synonymMap;
}

QueryResult QueryEvaluator::evaluate(QNode* node) {
    if (node->getQType() == CONDITIONLIST ||
            node->getQType() == QUERY) {
        vector <string> emptySynonym;
        QueryResult result = QueryResult(true);

        vector<QNode*> children = node->getChildren();
        for (int i = 0; i < (int)children.size(); i++) {
            if (children[i]->getQType() == CONDITIONLIST ||
                    children[i]->getQType() == RELATION ||
                    children[i]->getQType() == PATTERN)
                result = result.merge(evaluate(children[i]));
        }


        return result;
    } else if (node->getQType() == RELATION) {
        QueryResult result = solveRelation(node);
        return result;
    } else if (node->getQType() == PATTERN) {
        return solvePattern(node);
    }
}

QueryResult QueryEvaluator::solveRelation(QNode* node) {
    assert(node->getQType() == RELATION);
    if (node->getString() == "Follows") {
        return solveFollows(node);
    } else if (node->getString() == "Follows*") {
        return solveFollowsStar(node);
    } else if (node->getString() == "Parent") {
        return solveParent(node);
    } else if (node->getString() == "Parent*") {
        return solveParentStar(node);
    } else if (node->getString() == "Modifies") {
        return solveModifies(node);
    } else if (node->getString() == "Uses") {
        return solveUses(node);
    } else if (node->getString() == "Calls") {
        return solveCalls(node);
    } else if (node->getString() == "Calls*") {
        return solveCallsStar(node);
    }
}


QueryResult QueryEvaluator::solveFollows(QNode* node) {
    FollowsEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveFollowsStar(QNode* node) {
    FollowsStarEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveParent(QNode* node) {
    ParentEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveParentStar(QNode* node) {
    ParentStarEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveModifies(QNode* node) {
    assert(node->getQType() == RELATION && node->getString() == "Modifies");
    ModifiesEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveUses(QNode* node) {
    assert(node->getQType() == RELATION && node->getString() == "Uses");
    UsesEvaluator eval(pkbInstance);
    QueryResult result = eval.evaluate(node);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveCalls(QNode* node) {
    assert(node->getQType() == RELATION && node->getString() == "Calls");
    CallsEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solveCallsStar(QNode* node) {
    CallsStarEvaluator eval(pkbInstance);
    return eval.evaluate(node);
}

QueryResult QueryEvaluator::solvePattern(QNode* node) {
    assert(node->getQType() == PATTERN);
    QNode* assignNode = node->getChildren()[0];
    QNode* varNode = node->getChildren()[1];
    string expression = node->getChildren()[2]->getString();
    if (varNode->getQType() == ANY) {
        vector <string> vars = pkbInstance->getVarTable()->getAllVarName();
        vector <QueryResult> results;
        for (int i = 0; i < (int) vars.size(); i++) {
            QNode* node = new QNode(PATTERN, "");
            QNode* newAssignNode = new QNode(assignNode->getQType(), assignNode->getString());
            QNode* newVarNode = new QNode(CONST, vars[i]);
            QNode* newExpressionNode = new QNode(CONST, expression);
            node->addChild(newAssignNode);
            node->addChild(newVarNode);
            node->addChild(newExpressionNode);
            results.push_back(solvePattern(node));
            delete newAssignNode;
            delete newVarNode;
            delete newExpressionNode;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    bool strict = true;
    bool any = false;
    if (expression[0] == '_' && (int) expression.length() > 1) {
        //non-strict
        expression = expression.substr(1, expression.length() - 2);
        strict = false;
    } else if (expression[0] == '_') {
        any = true;
    }

    if (isSynonym(varNode->getQType())) {
        vector<pair<int,int> > resultPairs;
        vector<STMTLINE> assignments = pkbInstance->getAst()->getStmtLines(ASSIGNN);
        for (int i = 0; i < (int) assignments.size(); i++) {
            vector<VARINDEX> variables = pkbInstance->getVarTable()->getAllVarIndex();
            for (int j = 0; j < (int) variables.size(); j++) {
                if (pkbInstance->getAst()->matchLeftPattern(assignments[i], variables[j]) &&
                        (any || pkbInstance->getAst()->matchRightPattern(assignments[i], expression, strict))) {
                    resultPairs.push_back(make_pair(assignments[i], variables[j]));
                }
            }
        }
        return QueryResult(resultPairs, assignNode->getString(), varNode->getString());
    } else {
        vector<int> resultList;
        vector<STMTLINE> assignments = pkbInstance->getAst()->getStmtLines(ASSIGNN);
        VARINDEX variable = pkbInstance->getVarTable()->getVarIndex(varNode->getString());
        for (int i = 0; i < (int) assignments.size(); i++) {
            if (pkbInstance->getAst()->matchLeftPattern(assignments[i], variable) &&
                    (any || pkbInstance->getAst()->matchRightPattern(assignments[i], expression, strict))) {
                resultList.push_back(assignments[i]);
            }
        }
        return QueryResult(resultList, assignNode->getString());
    }
}


int QueryEvaluator::getInteger(QNode* node) {
    istringstream iss(node->getString());
    int result;
    iss >> result;
    return result;
}

TType QueryEvaluator::synonymToTType(QNodeType type) {
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
	}
}

bool QueryEvaluator::isSynonym(QNodeType type) {
    return type == WHILESYNONYM ||
           type == ASSIGNSYNONYM ||
           type == VARIABLESYNONYM ||
           type == PROCEDURESYNONYM ||
           type == CONSTSYNONYM ||
           type == PROGLINESYNONYM ||
           type == IFSYNONYM ||
           type == STMTSYNONYM;
}