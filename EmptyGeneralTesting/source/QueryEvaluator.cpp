#include "QueryEvaluator.h"

string QueryEvaluator::evaluate(QueryTree* tree) {
    return "Incomplete Stub Method";
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
	}
}


QueryResult QueryEvaluator::solveFollows(QNode* node) {
	assert(node->getQType() == RELATION && node->getString() == "Follows");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (isSynonym(leftChild->getQType()) && isSynonym(rightChild->getQType())) {
		TType type1 = synonymToTType(leftChild->getQType());
		TType type2 = synonymToTType(rightChild->getQType());
		return pairsToResult(Follows(type1, type2), 
			leftChild->getString(), rightChild->getString());
	} else if (isSynonym(leftChild->getQType())) {
		int line = getInteger(rightChild);
		int resultLine = pkbInstance.getFollows()->getFollowsFrom(line);
		return oneToResult(resultLine, leftChild->getString());
	} else if (isSynonym(rightChild->getQType())) {
		int line = getInteger(leftChild);
		int resultLine = pkbInstance.getFollows()->getFollowedBy(line);
		return oneToResult(resultLine, leftChild->getString());
	} else {
		int line1 = getInteger(leftChild);
		int line2 = getInteger(rightChild);
		return boolToResult(pkbInstance.getFollows()->isFollows(line1, line2));
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

QueryResult QueryEvaluator::boolToResult(bool boolResult) {
	vector <string> synonyms;
	QueryResult result = QueryResult(synonyms);

	if (boolResult) {
		result.addSolution(vector<int>());
	}
	return result;
}

QueryResult QueryEvaluator::pairsToResult(vector<pair<int,int> > pairs, string synonym1, string synonym2) {
	vector <string> synonyms;
	synonyms.push_back(synonym1);
	synonyms.push_back(synonym2);
	QueryResult result = QueryResult(synonyms);

	for (int i = 0; i < (int) pairs.size(); i++) {
		vector <int> resultTuple;
		resultTuple.push_back(pairs[i].first);
		resultTuple.push_back(pairs[i].second);
		result.addSolution(resultTuple);
	}
	return result;
}

QueryResult QueryEvaluator::oneToResult(int oneresult, string synonym) {
	vector <int> singles;
	singles.push_back(oneresult);

	return singlesToResult(singles, synonym);
}

QueryResult QueryEvaluator::singlesToResult(vector<int> singles, string synonym) {
	vector<string> synonyms;
	synonyms.push_back(synonym);
	QueryResult result(synonyms);
	for (int i = 0; i < (int)singles.size(); i++) {
		vector<int> tuple;
		tuple.push_back(singles[i]);
		result.addSolution(tuple);
	}
	return result;	
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

	return singlesToResult(possibleResult, synonym);
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
