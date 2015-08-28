#include "QueryEvaluator.h"
#include "FollowsEvaluator.h"
#include "FollowsStarEvaluator.h"
#include "ParentEvaluator.h"

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
                //TODO: link to procedure
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
            //TODO
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
    if (node->getQType() == SUCHTHATLIST ||
            node->getQType() == WITHLIST ||
            node->getQType() == PATTERNLIST ||
            node->getQType() == QUERY) {
        vector <string> emptySynonym;
        QueryResult result =QueryResult(true);

        vector<QNode*> children = node->getChildren();
        for (int i = 0; i < (int)children.size(); i++) {
            if (children[i]->getQType() == SUCHTHATLIST ||
                    children[i]->getQType() == WITHLIST ||
                    children[i]->getQType() == RELATION ||
                    children[i]->getQType() == PATTERNLIST ||
                    children[i]->getQType() == PATTERN)
                result = result.merge(evaluate(children[i]));
        }

        return result;
    } else if (node->getQType() == RELATION) {
        return solveRelation(node);
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
    assert(node->getQType() == RELATION && node->getString() == "Parent*");
    QNode* leftChild = node->getChildren()[0];
    QNode* rightChild = node->getChildren()[1];
    if (leftChild->getQType() == ANY) {
        vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
        vector <QueryResult> results;
        for (int i = 0; i < (int) statements.size(); i++) {
            stringstream s;
            s << statements[i];
            QNode* node = new QNode(RELATION, "Parent*");
            QNode* newLeftChild = new QNode(CONST, s.str());
            QNode* newRightChild = new QNode(rightChild->getQType(), rightChild->getString());
            node->addChild(newLeftChild);
            node->addChild(newRightChild);
            results.push_back(solveParentStar(node));
            delete newLeftChild;
            delete newRightChild;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    if (rightChild->getQType() == ANY) {
        vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
        vector <QueryResult> results;
        for (int i = 0; i < (int) statements.size(); i++) {
            stringstream s;
            s << statements[i];
            QNode* node = new QNode(RELATION, "Parent*");
            QNode* newLeftChild = new QNode(leftChild->getQType(), leftChild->getString());
            QNode* newRightChild = new QNode(CONST, s.str());
            node->addChild(newLeftChild);
            node->addChild(newRightChild);
            results.push_back(solveParentStar(node));
            delete newLeftChild;
            delete newRightChild;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    if (isSynonym(leftChild->getQType()) && isSynonym(rightChild->getQType())) {
        TType type1 = synonymToTType(leftChild->getQType());
        TType type2 = synonymToTType(rightChild->getQType());

        return QueryResult(ParentStar(type1, type2),
                           leftChild->getString(), rightChild->getString());
    } else if (isSynonym(leftChild->getQType())) {
        int line = getInteger(rightChild);
        vector<int> resultLines = pkbInstance->getParent()->getParentStar(line);
        resultLines = filter(resultLines, synonymToTType(leftChild->getQType()));
        return QueryResult(resultLines, leftChild->getString());
    } else if (isSynonym(rightChild->getQType())) {
        int line = getInteger(leftChild);
        vector<int> resultLines = pkbInstance->getParent()->getChildOfStar(line);
        resultLines = filter(resultLines, synonymToTType(rightChild->getQType()));
        return QueryResult(resultLines, rightChild->getString());
    } else {
        int line1 = getInteger(leftChild);
        int line2 = getInteger(rightChild);
        return QueryResult(pkbInstance->getParent()->isParentStar(line1, line2));
    }
}

QueryResult QueryEvaluator::solveModifies(QNode* node) {
    assert(node->getQType() == RELATION && node->getString() == "Modifies");
    QNode* leftChild = node->getChildren()[0];
    QNode* rightChild = node->getChildren()[1];
    if (leftChild->getQType() == ANY) {
        vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
        vector <QueryResult> results;
        for (int i = 0; i < (int) statements.size(); i++) {
            stringstream s;
            s << statements[i];
            QNode* node = new QNode(RELATION, "Modifies");
            QNode* newLeftChild = new QNode(CONST, s.str());
            QNode* newRightChild = new QNode(rightChild->getQType(), rightChild->getString());
            node->addChild(newLeftChild);
            node->addChild(newRightChild);
            results.push_back(solveModifies(node));
            delete newLeftChild;
            delete newRightChild;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    if (rightChild->getQType() == ANY) {
        vector <string> vars = pkbInstance->getVarTable()->getAllVarName();
        vector <QueryResult> results;
        for (int i = 0; i < (int) vars.size(); i++) {
            QNode* node = new QNode(RELATION, "Modifies");
            QNode* newLeftChild = new QNode(leftChild->getQType(), leftChild->getString());
            QNode* newRightChild = new QNode(CONST, vars[i]);
            node->addChild(newLeftChild);
            node->addChild(newRightChild);
            results.push_back(solveModifies(node));
            delete newLeftChild;
            delete newRightChild;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    if (isSynonym(leftChild->getQType()) && isSynonym(rightChild->getQType())) {
        TType type = synonymToTType(leftChild->getQType());

        return QueryResult(Modifies(type),
                           leftChild->getString(), rightChild->getString());
    } else if (isSynonym(leftChild->getQType())) {
        VARNAME var = rightChild->getString();
        int varIndex = pkbInstance->getVarTable()->getVarIndex(var);

        vector<STMTLINE> lines = pkbInstance->getModifies()->getModifies(varIndex);

        lines = filter(lines, synonymToTType(leftChild->getQType()));

        return QueryResult(lines, leftChild->getString());
    } else if (isSynonym(rightChild->getQType())) {
        STMTLINE line = getInteger(leftChild);

        return QueryResult(pkbInstance->getModifies()->getModifiedByStmt(line),
                           rightChild->getString());
    } else {
        VARNAME var = rightChild->getString();
        int varIndex = pkbInstance->getVarTable()->getVarIndex(var);

        STMTLINE line = getInteger(leftChild);
        vector <VARINDEX> possibleVarIndex =
            pkbInstance->getModifies()->getModifiedByStmt(line);

        vector<VARINDEX>::iterator location;
        location = find(possibleVarIndex.begin(),
                        possibleVarIndex.end(),
                        varIndex);
        bool result = (location != possibleVarIndex.end());

        return QueryResult(result);
    }
}

QueryResult QueryEvaluator::solveUses(QNode* node) {
    assert(node->getQType() == RELATION && node->getString() == "Uses");
    QNode* leftChild = node->getChildren()[0];
    QNode* rightChild = node->getChildren()[1];
    if (leftChild->getQType() == ANY) {
        vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
        vector <QueryResult> results;
        for (int i = 0; i < (int) statements.size(); i++) {
            stringstream s;
            s << statements[i];
            QNode* node = new QNode(RELATION, "Uses");
            QNode* newLeftChild = new QNode(CONST, s.str());
            QNode* newRightChild = new QNode(rightChild->getQType(), rightChild->getString());
            node->addChild(newLeftChild);
            node->addChild(newRightChild);
            results.push_back(solveUses(node));
            delete newLeftChild;
            delete newRightChild;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    if (rightChild->getQType() == ANY) {
        vector <string> vars = pkbInstance->getVarTable()->getAllVarName();
        vector <QueryResult> results;
        for (int i = 0; i < (int) vars.size(); i++) {
            QNode* node = new QNode(RELATION, "Uses");
            QNode* newLeftChild = new QNode(leftChild->getQType(), leftChild->getString());
            QNode* newRightChild = new QNode(CONST, vars[i]);
            node->addChild(newLeftChild);
            node->addChild(newRightChild);
            results.push_back(solveUses(node));
            delete newLeftChild;
            delete newRightChild;
            delete node;
        }
        for (int j = 1; j < (int) results.size(); j++) {
            results[0].append(results[j]);
        }
        return results[0];
    }
    if (isSynonym(leftChild->getQType()) && isSynonym(rightChild->getQType())) {
        TType type = synonymToTType(leftChild->getQType());

        return QueryResult(Uses(type),
                           leftChild->getString(), rightChild->getString());
    } else if (isSynonym(leftChild->getQType())) {
        VARNAME var = rightChild->getString();
        int varIndex = pkbInstance->getVarTable()->getVarIndex(var);

        vector<STMTLINE> lines = pkbInstance->getUses()->getUses(varIndex);

        lines = filter(lines, synonymToTType(leftChild->getQType()));

        return QueryResult(lines, leftChild->getString());
    } else if (isSynonym(rightChild->getQType())) {
        STMTLINE line = getInteger(leftChild);

        return QueryResult(pkbInstance->getUses()->getUsedByStmt(line),
                           rightChild->getString());
    } else {
        VARNAME var = rightChild->getString();
        int varIndex = pkbInstance->getVarTable()->getVarIndex(var);

        STMTLINE line = getInteger(leftChild);
        vector <VARINDEX> possibleVarIndex =
            pkbInstance->getUses()->getUsedByStmt(line);

        vector<VARINDEX>::iterator location;
        location = find(possibleVarIndex.begin(),
                        possibleVarIndex.end(),
                        varIndex);
        bool result = (location != possibleVarIndex.end());

        return QueryResult(result);
    }
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


QueryResult QueryEvaluator::getAllOfType(TType t, string synonym) {
    vector <int> possibleResult;
    if (t == WHILEN || t == ASSIGNN) {
        possibleResult = pkbInstance->getAst()->getStmtLines(t);
    } else if (t == PROCEDUREN) {
        //TODO
    } else if (t == VARN) {
        possibleResult = pkbInstance->getVarTable()->getAllVarIndex();
    }

    return QueryResult(possibleResult, synonym);
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Follows(TType firstType, TType secondType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance->getAst()->getStmtLines(firstType);

    // retrieve all stmt# from AST that belongs to the secondType
    vector<STMTLINE> secondResult = pkbInstance->getAst()->getStmtLines(secondType);

    vector<std::pair<STMTLINE, STMTLINE>> result;

    // double for loop based on both vector of stmt#, check Follows() is true then keep into vector as tuple.
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        for(std::vector<STMTLINE>::iterator k = secondResult.begin(); k != secondResult.end(); ++k) {
            if(pkbInstance->getFollows()->isFollows(*j, *k)) {
                result.push_back(std::make_pair(*j, *k));
            }
        }
    }

    // return the vector of tuples
    return result;
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::FollowsStar(TType firstType, TType secondType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance->getAst()->getStmtLines(firstType);

    // retrieve all stmt# from AST that belongs to the secondType
    vector<STMTLINE> secondResult = pkbInstance->getAst()->getStmtLines(secondType);

    vector<std::pair<STMTLINE, STMTLINE>> result;

    // double for loop based on both vector of stmt#, check Follows() is true then keep into vector as tuple.
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        for(std::vector<STMTLINE>::iterator k = secondResult.begin(); k != secondResult.end(); ++k) {
            if(pkbInstance->getFollows()->isFollowsStar(*j, *k)) {
                result.push_back(std::make_pair(*j, *k));
            }
        }
    }

    // return the vector of tuples
    return result;
}


vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Parent(TType firstType, TType secondType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance->getAst()->getStmtLines(firstType);

    // retrieve all stmt# from AST that belongs to the secondType
    vector<STMTLINE> secondResult = pkbInstance->getAst()->getStmtLines(secondType);

    vector<std::pair<STMTLINE, STMTLINE>> result;

    // double for loop based on both vector of stmt#, check Parent() is true then keep into vector as tuple.
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        for(std::vector<STMTLINE>::iterator k = secondResult.begin(); k != secondResult.end(); ++k) {
            if(pkbInstance->getParent()->isParent(*j, *k)) {
                result.push_back(std::make_pair(*j, *k));
            }
        }
    }

    // return the vector of tuples
    return result;
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::ParentStar(TType firstType, TType secondType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance->getAst()->getStmtLines(firstType);

    // retrieve all stmt# from AST that belongs to the secondType
    vector<STMTLINE> secondResult = pkbInstance->getAst()->getStmtLines(secondType);

    vector<std::pair<STMTLINE, STMTLINE>> result;

    // double for loop based on both vector of stmt#, check Parent() is true then keep into vector as tuple.
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        for(std::vector<STMTLINE>::iterator k = secondResult.begin(); k != secondResult.end(); ++k) {
            if(pkbInstance->getParent()->isParentStar(*j, *k)) {
                result.push_back(std::make_pair(*j, *k));
            }
        }
    }

    // return the vector of tuples
    return result;
}

vector<std::pair<STMTLINE, VARINDEX>> QueryEvaluator::Modifies(TType firstType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance->getAst()->getStmtLines(firstType);

    vector<std::pair<STMTLINE, VARINDEX>> result;

    // for each stmt#, store all combination tuple of the # and var that it modifies
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        vector<VARINDEX> jResult = pkbInstance->getModifies()->getModifiedByStmt(*j);
        for(std::vector<VARINDEX>::iterator k = jResult.begin(); k != jResult.end(); ++k) {
            result.push_back(std::make_pair(*j, *k));
        }
    }

    // return the vector of tuples
    return result;

}

vector<std::pair<STMTLINE, VARINDEX>> QueryEvaluator::Uses(TType firstType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance->getAst()->getStmtLines(firstType);

    vector<std::pair<STMTLINE, VARINDEX>> result;

    // for each stmt#, store all combination tuple of the # and var that it uses
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        vector<VARINDEX> jResult = pkbInstance->getUses()->getUsedByStmt(*j);
        for(std::vector<VARINDEX>::iterator k = jResult.begin(); k != jResult.end(); ++k) {
            result.push_back(std::make_pair(*j, *k));
        }
    }

    // return the vector of tuples
    return result;

}