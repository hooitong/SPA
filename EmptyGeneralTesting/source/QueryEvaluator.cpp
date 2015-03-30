#include "QueryEvaluator.h"

string QueryEvaluator::evaluate(QueryTree* tree) {
    QueryResult result = evaluate(tree->getRoot());
	
	vector <string> resultSynonym;
	map <string, TType> synonymMap;

	vector <QNode*> children = tree->getRoot()->getChildren();
	for (int i = 0; i < (int) children.size(); i++) {
		if (children[i]->getQType() == RESULTLIST) {
			resultSynonym = getResultSynonyms(children[i]);
			synonymMap = getSynonymMap(children[i]);
		}
	}

	result.filter(resultSynonym);

	vector <vector<int> > solutions = result.getResult();

	ostringstream oss;
	for (int i = 0; i < (int)solutions.size(); i++) {
		if (i > 0) {
			oss << ", ";
		}
		if (solutions[i].size() > 1) {
			oss << "<";
		}
		for (int j = 0; j < (int) solutions[i].size(); j++) {
			if (j > 0) {
				oss << ", ";
			}

			if (synonymMap[resultSynonym[j]] == VARN) {
				oss << pkbInstance.getVarTable()->getVarName(solutions[i][j]);
			} else if (synonymMap[resultSynonym[j]] == PROCEDUREN) {
				//TODO: link to procedure
			} else {
				oss << solutions[i][j];
			}
		}
		if (solutions[i].size() > 1) {
			oss << ">";
		}
	}

	return oss.str();
}

vector<string> QueryEvaluator::getResultSynonyms(QNode* node) {
	assert(node->getQType() == RESULTLIST);
	vector <string> result;
	vector<QNode*> children = node->getChildren();
	for (int i = 0; i < (int) children.size(); i++) {
		result.push_back(children[i]->getString());	
	}
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
		node->getQType() == PATTERNLIST) {
		vector <string> emptySynonym;
		QueryResult result =QueryResult(emptySynonym);

		vector<QNode*> children = node->getChildren();
		for (int i = 0; i < (int)children.size(); i++) {
			result = result.merge(evaluate(children[i]));
		}

		return result;
	} else if (node->getQType() == RELATION) {
		return solveRelation(node);
	}
}

QueryResult QueryEvaluator::solveRelation(QNode* node) {
	assert(node->getQType() == RELATION);
	if (node->getString() == "Follows") {
		return solveFollows(node);
	} else if (node->getString() == "Parent") {
		return solveParent(node);
	} else if (node->getString() == "Modifies") {
		//TODO: Link to modifies
	}
}


QueryResult QueryEvaluator::solveFollows(QNode* node) {
	assert(node->getQType() == RELATION && node->getString() == "Follows");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (isSynonym(leftChild->getQType()) && isSynonym(rightChild->getQType())) {
		TType type1 = synonymToTType(leftChild->getQType());
		TType type2 = synonymToTType(rightChild->getQType());
		return QueryResult(Follows(type1, type2), 
			leftChild->getString(), rightChild->getString());
	} else if (isSynonym(leftChild->getQType())) {
		int line = getInteger(rightChild);
		int resultLine = pkbInstance.getFollows()->getFollowsFrom(line);
		return QueryResult(resultLine, leftChild->getString());
	} else if (isSynonym(rightChild->getQType())) {
		int line = getInteger(leftChild);
		int resultLine = pkbInstance.getFollows()->getFollowedBy(line);
		return QueryResult(resultLine, leftChild->getString());
	} else {
		int line1 = getInteger(leftChild);
		int line2 = getInteger(rightChild);
		return QueryResult(pkbInstance.getFollows()->isFollows(line1, line2));
	}
}

QueryResult QueryEvaluator::solveParent(QNode* node) {
	assert(node->getQType() == RELATION && node->getString() == "Parent");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (isSynonym(leftChild->getQType()) && isSynonym(rightChild->getQType())) {
		TType type1 = synonymToTType(leftChild->getQType());
		TType type2 = synonymToTType(rightChild->getQType());
		return QueryResult(Parent(type1, type2), 
			leftChild->getString(), rightChild->getString());
	} else if (isSynonym(leftChild->getQType())) {
		int line = getInteger(rightChild);
		int resultLine = pkbInstance.getParent()->getParent(line);
		return QueryResult(resultLine, leftChild->getString());
	} else if (isSynonym(rightChild->getQType())) {
		int line = getInteger(leftChild);
		vector<int> resultLines = pkbInstance.getParent()->getChildOf(line);
		return QueryResult(resultLines, leftChild->getString());
	} else {
		int line1 = getInteger(leftChild);
		int line2 = getInteger(rightChild);
		return QueryResult(pkbInstance.getParent()->isParent(line1, line2));
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
	}
}

bool QueryEvaluator::isSynonym(QNodeType type) {
	return type == WHILESYNONYM ||
		type == ASSIGNSYNONYM ||
		type == VARIABLESYNONYM ||
		type == PROCEDURESYNONYM ||
		type == CONSTSYNONYM ||
		type == PROGLINESYNONYM ||
		type == IFSYNONYM;
}


QueryResult QueryEvaluator::getAllOfType(TType t, string synonym) {
	vector <int> possibleResult;
	if (t == WHILEN || t == ASSIGNN) {
		possibleResult = pkbInstance.getAst()->getStmtLines(t);
	} else if (t == PROCEDUREN) {
		//TODO
	} else if (t == VARN) {
		possibleResult = pkbInstance.getVarTable()->getAllVarIndex();
	}

	return QueryResult(possibleResult, synonym);
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Follows(TType firstType, TType secondType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance.getAst()->getStmtLines(firstType);

    // retrieve all stmt# from AST that belongs to the secondType
    vector<STMTLINE> secondResult = pkbInstance.getAst()->getStmtLines(secondType);

    vector<std::pair<STMTLINE, STMTLINE>> result;

    // double for loop based on both vector of stmt#, check Follows() is true then keep into vector as tuple.
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        for(std::vector<STMTLINE>::iterator k = firstResult.begin(); k != firstResult.end(); ++k) {
            if(pkbInstance.getFollows()->isFollows(*j, *k)) {
                result.push_back(std::make_pair(*j, *k));
            }
        }
    }

    // return the vector of tuples
    return result;
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Parent(TType firstType, TType secondType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance.getAst()->getStmtLines(firstType);

    // retrieve all stmt# from AST that belongs to the secondType
    vector<STMTLINE> secondResult = pkbInstance.getAst()->getStmtLines(secondType);

    vector<std::pair<STMTLINE, STMTLINE>> result;

    // double for loop based on both vector of stmt#, check Parent() is true then keep into vector as tuple.
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        for(std::vector<STMTLINE>::iterator k = firstResult.begin(); k != firstResult.end(); ++k) {
            if(pkbInstance.getParent()->isParent(*j, *k)) {
                result.push_back(std::make_pair(*j, *k));
            }
        }
    }

    // return the vector of tuples
    return result;
}

vector<std::pair<STMTLINE, VARINDEX>> QueryEvaluator::Modifies(TType firstType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance.getAst()->getStmtLines(firstType);

    vector<std::pair<STMTLINE, VARINDEX>> result;

    // for each stmt#, store all combination tuple of the # and var that it modifies
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        vector<VARINDEX> jResult = pkbInstance.getModifies()->getModifiedByStmt(*j);
        for(std::vector<VARINDEX>::iterator k = jResult.begin(); k != jResult.end(); ++k) {
            result.push_back(std::make_pair(*j, *k));
        }
    }

    // return the vector of tuples
    return result;

}

vector<std::pair<STMTLINE, VARINDEX>> QueryEvaluator::Uses(TType firstType) {
    // retrieve all stmt# from AST that belongs to the firstType
    vector<STMTLINE> firstResult = pkbInstance.getAst()->getStmtLines(firstType);

    vector<std::pair<STMTLINE, VARINDEX>> result;

    // for each stmt#, store all combination tuple of the # and var that it uses
    for(std::vector<STMTLINE>::iterator j = firstResult.begin(); j != firstResult.end(); ++j) {
        vector<VARINDEX> jResult = pkbInstance.getUses()->getUsedByStmt(*j);
        for(std::vector<VARINDEX>::iterator k = jResult.begin(); k != jResult.end(); ++k) {
            result.push_back(std::make_pair(*j, *k));
        }
    }

    // return the vector of tuples
    return result;

}
