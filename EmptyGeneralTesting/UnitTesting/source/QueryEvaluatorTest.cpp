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
// Based on the following SIMPLE program
/*
procedure Daisy {
1. a = 10;
2. c = a + 4;
3. i = 14 + a;
4. b = x + a * c;
5. while i {
6.   b = c - t;
7.   while a {
8.     t = t + a;
9.     i = t + 1;
10.    c = t + a;
11.    i = i - 17; }
12.  c = t + a; }
*/
void QueryEvaluatorTest::setupTestData() {
	Follows* fObj = pkbObj->getFollows();
	fObj->setFollows(1, 2);
	fObj->setFollows(2, 3);
	fObj->setFollows(3, 4);
	fObj->setFollows(4, 5);
	fObj->setFollows(6, 7);
	fObj->setFollows(7, 12);
	fObj->setFollows(8, 9);
	fObj->setFollows(9, 10);
	fObj->setFollows(10, 11);
	fObj->setFollowsStar(1, 2);
	fObj->setFollowsStar(1, 3);
	fObj->setFollowsStar(1, 4);
	fObj->setFollowsStar(1, 5);
	fObj->setFollowsStar(2, 3);
	fObj->setFollowsStar(2, 4);
	fObj->setFollowsStar(2, 5);
	fObj->setFollowsStar(3, 4);
	fObj->setFollowsStar(3, 5);
	fObj->setFollowsStar(4, 5);
	fObj->setFollowsStar(6, 7);
	fObj->setFollowsStar(6, 12);
	fObj->setFollowsStar(7, 12);
	
	fObj->setFollowsStar(8, 9);
	fObj->setFollowsStar(8, 10);
	fObj->setFollowsStar(8, 11);
	fObj->setFollowsStar(9, 10);
	fObj->setFollowsStar(9, 11);
	fObj->setFollowsStar(10, 11);

	Parent* pObj = pkbObj->getParent();
	pObj->setParent(5, 6);
	pObj->setParent(5, 7);
	pObj->setParent(5, 12);
	pObj->setParent(7, 8);
	pObj->setParent(7, 9);
	pObj->setParent(7, 10);
	pObj->setParent(7, 11);
	pObj->setParentStar(5, 6);
	pObj->setParentStar(5, 7);
	pObj->setParentStar(5, 12);
	pObj->setParentStar(5, 8);
	pObj->setParentStar(5, 9);
	pObj->setParentStar(5, 10);
	pObj->setParentStar(5, 11);
	pObj->setParentStar(7, 8);
	pObj->setParentStar(7, 9);
	pObj->setParentStar(7, 10);
	pObj->setParentStar(7, 11);

	VarTable* vObj = pkbObj->getVarTable();
	int a = vObj->insertVar("a");
	int b = vObj->insertVar("b");
	int c = vObj->insertVar("c");
	int i = vObj->insertVar("i");
	int t = vObj->insertVar("t");
	int x = vObj->insertVar("x");

	Modifies* mObj = pkbObj->getModifies();
	mObj->setModifiesStmt(1, a);
	mObj->setModifiesStmt(2, c);
	mObj->setModifiesStmt(3, i);
	mObj->setModifiesStmt(4, b);
	mObj->setModifiesStmt(5, b);
	mObj->setModifiesStmt(5, c);
	mObj->setModifiesStmt(5, i);
	mObj->setModifiesStmt(5, t);
	mObj->setModifiesStmt(6, b);
	mObj->setModifiesStmt(7, c);
	mObj->setModifiesStmt(7, i);
	mObj->setModifiesStmt(7, t);
	mObj->setModifiesStmt(8, t);
	mObj->setModifiesStmt(9, i);
	mObj->setModifiesStmt(10, c);
	mObj->setModifiesStmt(11, i);
	mObj->setModifiesStmt(12, c);
	mObj->setModifiesStmt(1, 7);

	Uses* uObj = pkbObj->getUses();
	uObj->setUsesStmt(2, a);
	uObj->setUsesStmt(3, a);
	uObj->setUsesStmt(4, a);
	uObj->setUsesStmt(4, c);
	uObj->setUsesStmt(4, x);
	uObj->setUsesStmt(5, a);
	uObj->setUsesStmt(5, c);
	uObj->setUsesStmt(5, i);
	uObj->setUsesStmt(5, t);
	uObj->setUsesStmt(6, c);
	uObj->setUsesStmt(6, t);
	uObj->setUsesStmt(7, a);
	uObj->setUsesStmt(7, i);
	uObj->setUsesStmt(7, t);
	uObj->setUsesStmt(8, a);
	uObj->setUsesStmt(8, t);
	uObj->setUsesStmt(9, t);
	uObj->setUsesStmt(10, a);
	uObj->setUsesStmt(10, t);
	uObj->setUsesStmt(11, i);
	uObj->setUsesStmt(12, a);
	uObj->setUsesStmt(12, t);


	AST* aObject = pkbObj->getAst();
	aObject->addToStmtLineMap(ASSIGNN, 1);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 1);
	aObject->addToStmtLineMap(ASSIGNN, 2);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 2);
	aObject->addToStmtLineMap(ASSIGNN, 3);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 3);
	aObject->addToStmtLineMap(ASSIGNN, 4);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 4);
	aObject->addToStmtLineMap(WHILEN, 5);
	aObject->setStmtLine(aObject->createTNode(WHILEN, ""), 5);
	aObject->addToStmtLineMap(ASSIGNN, 6);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 6);
	aObject->addToStmtLineMap(WHILEN, 7);
	aObject->setStmtLine(aObject->createTNode(WHILEN, ""), 7);
	aObject->addToStmtLineMap(ASSIGNN, 8);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 8);
	aObject->addToStmtLineMap(ASSIGNN, 9);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 9);
	aObject->addToStmtLineMap(ASSIGNN, 10);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 10);
	aObject->addToStmtLineMap(ASSIGNN, 11);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 11);
	aObject->addToStmtLineMap(ASSIGNN, 12);
	aObject->setStmtLine(aObject->createTNode(ASSIGNN, ""), 12);
}


CPPUNIT_TEST_SUITE_REGISTRATION(QueryEvaluatorTest);

QueryTree* QueryEvaluatorTest::createTree(
		QNodeType typeResult,
		string resultString,
		string relationString, 
		QNodeType type1, 
		string s1, 
		QNodeType type2, 
		string s2) {
	QueryTree* tree = new QueryTree();
	QNode* query = tree->createNode(QUERY, "");
	QNode* resultList = tree->createNode(RESULTLIST, "");
	QNode* result1 = tree->createNode(typeResult, resultString);
	QNode* suchThatList = tree->createNode(SUCHTHATLIST, "");
	QNode* relation = tree->createNode(RELATION, relationString);
	QNode* arg1 = tree->createNode(type1, s1);
	QNode* arg2 = tree->createNode(type2, s2);

	
	tree->setAsRoot(query);
	tree->addChild(query, resultList);
	tree->addChild(query, suchThatList);
	tree->addChild(resultList, result1);
	tree->addChild(suchThatList, relation);
	tree->addChild(relation, arg1);
	tree->addChild(relation, arg2);
	return tree;
}

// To test whether the Follow method is able to handle wildcards
void QueryEvaluatorTest::testFollowsLeft() {
	QueryTree* tree;
	QueryEvaluator evaluator(pkbObj);
	list<string> result;
	list<string> expected;
	tree = createTree(STMTSYNONYM, "s", "Follows", STMTSYNONYM, "s", CONST, "2");

	expected.clear();
	expected.push_back("1");
	result = evaluator.evaluate(tree);
	CPPUNIT_ASSERT(result == expected);
	delete tree;

	tree = createTree(WHILESYNONYM, "w", "Follows", STMTSYNONYM, "s", CONST, "1");

	expected.clear();
	result = evaluator.evaluate(tree);
	CPPUNIT_ASSERT(result == expected);
	delete tree;
}