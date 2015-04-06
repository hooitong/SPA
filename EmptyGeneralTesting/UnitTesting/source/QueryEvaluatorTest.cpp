#include <cppunit/config/SourcePrefix.h>

#include "QueryEvaluatorTest.h"

void QueryEvaluatorTest::setUp() {
	pkbObj = new PKB;
	setupTestData();
}

void QueryEvaluatorTest::tearDown() {
	delete pkbObj;
}

// setup sample data in the PKB for testing
void QueryEvaluatorTest::setupTestData() {
	Follows* fObj = pkbObj->getFollows();
	fObj->setFollows(1, 2);
	fObj->setFollows(3, 4);
	fObj->setFollows(5, 6);
	fObj->setFollows(4, 7);
	fObj->setFollowsStar(1, 2);
	fObj->setFollowsStar(3, 4);
	fObj->setFollowsStar(4, 7);
	fObj->setFollowsStar(3, 7);
	fObj->setFollowsStar(5, 6);

	Parent* pObj = pkbObj->getParent();
	pObj->setParent(4, 5);

	Modifies* mObj = pkbObj->getModifies();
	mObj->setModifiesStmt(1, 1);
	mObj->setModifiesStmt(1, 2);
	mObj->setModifiesStmt(2, 3);
	mObj->setModifiesStmt(3, 5);
	mObj->setModifiesStmt(4, 6);
	mObj->setModifiesStmt(1, 7);

	Uses* uObj = pkbObj->getUses();
	uObj->setUsesStmt(2, 1);
	uObj->setUsesStmt(3, 2);
	uObj->setUsesStmt(2, 3);
	uObj->setUsesStmt(3, 4);
	uObj->setUsesStmt(1, 5);
	uObj->setUsesStmt(4, 6);
	uObj->setUsesStmt(5, 7);

	AST* aObject = pkbObj->getAst();
	aObject->addToStmtLineMap(ASSIGNN, 1);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 1);
	aObject->addToStmtLineMap(ASSIGNN, 2);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 2);
	aObject->addToStmtLineMap(ASSIGNN, 3);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 3);
	aObject->addToStmtLineMap(ASSIGNN, 4);
	aObject->setStmtLine(aObject->createTNode(WHILEN, ""), 4);
	aObject->addToStmtLineMap(ASSIGNN, 5);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 5);
	aObject->addToStmtLineMap(ASSIGNN, 6);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 6);
	aObject->addToStmtLineMap(ASSIGNN, 7);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 7);
}


CPPUNIT_TEST_SUITE_REGISTRATION(QueryEvaluatorTest);

// To test whether the Follow method is able to handle wildcards
void QueryEvaluatorTest::testFollows() {
	QueryTree* tree = new QueryTree();
	QNode* query = tree->createNode(QUERY, "");
	QNode* resultList = tree->createNode(RESULTLIST, "");
	QNode* result1 = tree->createNode(ASSIGNSYNONYM, "a");
	QNode* suchThatList = tree->createNode(SUCHTHATLIST, "");
	QNode* follows = tree->createNode(RELATION, "Follows");
	QNode* arg1 = tree->createNode(ASSIGNSYNONYM, "a");
	QNode* arg2 = tree->createNode(CONST, "2");

	tree->setAsRoot(query);
	tree->addChild(query, resultList);
	tree->addChild(query, suchThatList);
	tree->addChild(resultList, result1);
	tree->addChild(suchThatList, follows);
	tree->addChild(follows, arg1);
	tree->addChild(follows, arg2);
	QueryEvaluator evaluator = QueryEvaluator(pkbObj);

	list<string> expected;
	expected.push_back("1");
	list<string> result = evaluator.evaluate(tree);
	CPPUNIT_ASSERT(result == expected);
}

void QueryEvaluatorTest::testFollowsStar() {
	QueryTree* tree = new QueryTree();
	QNode* query = tree->createNode(QUERY, "");
	QNode* resultList = tree->createNode(RESULTLIST, "");
	QNode* result1 = tree->createNode(ASSIGNSYNONYM, "a");
	QNode* suchThatList = tree->createNode(SUCHTHATLIST, "");
	QNode* follows = tree->createNode(RELATION, "Follows*");
	QNode* arg1 = tree->createNode(ASSIGNSYNONYM, "a");
	QNode* arg2 = tree->createNode(CONST, "7");

	tree->setAsRoot(query);
	tree->addChild(query, resultList);
	tree->addChild(query, suchThatList);
	tree->addChild(resultList, result1);
	tree->addChild(suchThatList, follows);
	tree->addChild(follows, arg1);
	tree->addChild(follows, arg2);
	QueryEvaluator evaluator = QueryEvaluator(pkbObj);

	list<string> expected;
	expected.push_back("3");
	list<string> result = evaluator.evaluate(tree);
	CPPUNIT_ASSERT(expected == result);
}

// To test whether the Parent method is able to handle wildcards
void QueryEvaluatorTest::testParentTuple() {

}

// To test whether the Modifies method is able to handle wildcards
void QueryEvaluatorTest::testModifiesTuple() {

}

// To test whether the Uses method is able to handle wildcards
void QueryEvaluatorTest::testUsesTuple() {

}