#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator() {
	pkbInstance = PKB::getPKB();
}

string QueryEvaluator::evaluate(QueryTree* tree) {
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
				oss << pkbInstance->getVarTable()->getVarName(solutions[i][j]);
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
			result.push_back(lineType);
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
	assert(node->getQType() == RELATION && node->getString() == "Follows");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (leftChild->getQType() == ANY) {
		vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
		vector <QueryResult> results;
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Follows*");
			QNode* leftChild = new QNode(CONST, s.str());
			QNode* rightChild = new QNode(rightChild->getQType(), rightChild->getString());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Follows*");
			QNode* leftChild = new QNode(leftChild->getQType(), leftChild->getString());
			QNode* rightChild = new QNode(CONST, s.str());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		return QueryResult(Follows(type1, type2), 
			leftChild->getString(), rightChild->getString());
	} else if (isSynonym(leftChild->getQType())) {
		int line = getInteger(rightChild);
		int resultLine = pkbInstance->getFollows()->getFollowsFrom(line);
		TType type = synonymToTType(leftChild->getQType());

		if (type != STMTN && 
			pkbInstance->getAst()->getTNode(resultLine)->getTType() != type) {
			return QueryResult(false);
		} else {
			return QueryResult(resultLine, leftChild->getString());
		}
	} else if (isSynonym(rightChild->getQType())) {
		int line = getInteger(leftChild);
		int resultLine = pkbInstance->getFollows()->getFollowedBy(line);
		TType type = synonymToTType(rightChild->getQType());

		if (type != STMTN && 
			pkbInstance->getAst()->getTNode(resultLine)->getTType() != type) {
			return QueryResult(false);
		} else {
			return QueryResult(resultLine, leftChild->getString());
		}
	} else {
		int line1 = getInteger(leftChild);
		int line2 = getInteger(rightChild);
		return QueryResult(pkbInstance->getFollows()->isFollows(line1, line2));
	}
}

QueryResult QueryEvaluator::solveFollowsStar(QNode* node) {
	assert(node->getQType() == RELATION && node->getString() == "Follows*");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (leftChild->getQType() == ANY) {
		vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
		vector <QueryResult> results;
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Follows*");
			QNode* leftChild = new QNode(CONST, s.str());
			QNode* rightChild = new QNode(rightChild->getQType(), rightChild->getString());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Follows*");
			QNode* leftChild = new QNode(leftChild->getQType(), leftChild->getString());
			QNode* rightChild = new QNode(CONST, s.str());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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

		return QueryResult(FollowsStar(type1, type2), 
			leftChild->getString(), rightChild->getString());
	} else if (isSynonym(leftChild->getQType())) {
		int line = getInteger(rightChild);
		vector<int> resultLines = pkbInstance->getFollows()->getFollowsFromStar(line);
		resultLines = filter(resultLines, synonymToTType(leftChild->getQType()));
		return QueryResult(resultLines, leftChild->getString());
	} else if (isSynonym(rightChild->getQType())) {
		int line = getInteger(leftChild);
		vector<int> resultLines = pkbInstance->getFollows()->getFollowedByStar(line);
		resultLines = filter(resultLines, synonymToTType(rightChild->getQType()));
		return QueryResult(resultLines, leftChild->getString());
	} else {
		int line1 = getInteger(leftChild);
		int line2 = getInteger(rightChild);
		return QueryResult(pkbInstance->getFollows()->isFollowsStar(line1, line2));
	}
}

QueryResult QueryEvaluator::solveParent(QNode* node) {
	assert(node->getQType() == RELATION && node->getString() == "Parent");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (leftChild->getQType() == ANY) {
		vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
		vector <QueryResult> results;
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Parent");
			QNode* leftChild = new QNode(CONST, s.str());
			QNode* rightChild = new QNode(rightChild->getQType(), rightChild->getString());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Parent");
			QNode* leftChild = new QNode(leftChild->getQType(), leftChild->getString());
			QNode* rightChild = new QNode(CONST, s.str());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		return QueryResult(Parent(type1, type2), 
			leftChild->getString(), rightChild->getString());
	} else if (isSynonym(leftChild->getQType())) {
		int line = getInteger(rightChild);
		int resultLine = pkbInstance->getParent()->getParent(line);
		TType type = synonymToTType(leftChild->getQType());

		if (type != STMTN && 
			pkbInstance->getAst()->getTNode(resultLine)->getTType() != type) {
			return QueryResult(false);
		}
		return QueryResult(resultLine, leftChild->getString());
	} else if (isSynonym(rightChild->getQType())) {
		int line = getInteger(leftChild);
		vector<int> resultLines = pkbInstance->getParent()->getChildOf(line);
		resultLines = filter(resultLines, synonymToTType(rightChild->getQType()));
		return QueryResult(resultLines, leftChild->getString());
	} else {
		int line1 = getInteger(leftChild);
		int line2 = getInteger(rightChild);
		return QueryResult(pkbInstance->getParent()->isParent(line1, line2));
	}
}

QueryResult QueryEvaluator::solveParentStar(QNode* node) {
	assert(node->getQType() == RELATION && node->getString() == "Parent*");
	QNode* leftChild = node->getChildren()[0];
	QNode* rightChild = node->getChildren()[1];
	if (leftChild->getQType() == ANY) {
		vector <STMTLINE> statements = pkbInstance->getAst()->getStmtLines(STMTN);
		vector <QueryResult> results;
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Parent*");
			QNode* leftChild = new QNode(CONST, s.str());
			QNode* rightChild = new QNode(rightChild->getQType(), rightChild->getString());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Parent*");
			QNode* leftChild = new QNode(leftChild->getQType(), leftChild->getString());
			QNode* rightChild = new QNode(CONST, s.str());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		return QueryResult(resultLines, leftChild->getString());
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
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Modifies");
			QNode* leftChild = new QNode(CONST, s.str());
			QNode* rightChild = new QNode(rightChild->getQType(), rightChild->getString());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) vars.size(); i++) {
			QNode* node = new QNode(RELATION, "Modifies");
			QNode* leftChild = new QNode(leftChild->getQType(), leftChild->getString());
			QNode* rightChild = new QNode(CONST, vars[i]);
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) statements.size(); i++) {
			stringstream s;
			s << statements[i];
			QNode* node = new QNode(RELATION, "Uses");
			QNode* leftChild = new QNode(CONST, s.str());
			QNode* rightChild = new QNode(rightChild->getQType(), rightChild->getString());
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
		for (int i = 1; i < (int) vars.size(); i++) {
			QNode* node = new QNode(RELATION, "Uses");
			QNode* leftChild = new QNode(leftChild->getQType(), leftChild->getString());
			QNode* rightChild = new QNode(CONST, vars[i]);
			node->addChild(leftChild);
			node->addChild(rightChild);
			results.push_back(solveParentStar(node));
			delete leftChild;
			delete rightChild;
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
	assert(node->getQType() == RELATION && node->getString() == "Pattern");
	QNode* assignNode = node->getChildren()[0];
	QNode* varNode = node->getChildren()[1];
	string expression = node->getChildren()[2]->getString();
	bool strict = true;
	if (expression[0] == '_') {
		//non-strict
		expression = expression.substr(1, expression.length() - 1);
		strict = false;
	}
	if (isSynonym(varNode->getQType())) {
		vector<pair<int,int> > resultPairs;
		vector<STMTLINE> assignments = pkbInstance->getAst()->getStmtLines(ASSIGNN);
		for (int i = 0; i < (int) assignments.size(); i++) {
			vector<VARINDEX> variables = pkbInstance->getVarTable()->getAllVarIndex();
			for (int j = 0; j < (int) variables.size(); j++) {
				if (pkbInstance->getAst()->matchLeftPattern(assignments[i], variables[j]) && 
					pkbInstance->getAst()->matchRightPattern(assignments[i], expression, false)) {
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
				pkbInstance->getAst()->matchRightPattern(assignments[i], expression, false)) {
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
        for(std::vector<STMTLINE>::iterator k = firstResult.begin(); k != firstResult.end(); ++k) {
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
        for(std::vector<STMTLINE>::iterator k = firstResult.begin(); k != firstResult.end(); ++k) {
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
        for(std::vector<STMTLINE>::iterator k = firstResult.begin(); k != firstResult.end(); ++k) {
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
        for(std::vector<STMTLINE>::iterator k = firstResult.begin(); k != firstResult.end(); ++k) {
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