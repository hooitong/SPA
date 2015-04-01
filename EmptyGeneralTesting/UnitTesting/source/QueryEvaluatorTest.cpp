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
	Follows fObj = *(*pkbObj).getFollows();
	fObj.setFollows(1, 2);
	fObj.setFollows(3, 4);
	fObj.setFollows(5, 6);
	fObj.setFollows(4, 7);

	Parent pObj = *(*pkbObj).getParent();
	pObj.setParent(4, 5);

	Modifies mObj = *(*pkbObj).getModifies();
	mObj.setModifiesStmt(1, 1);
	mObj.setModifiesStmt(1, 2);
	mObj.setModifiesStmt(2, 3);
	mObj.setModifiesStmt(3, 5);
	mObj.setModifiesStmt(4, 6);
	mObj.setModifiesStmt(1, 7);

	Uses uObj = *(*pkbObj).getUses();
	uObj.setUsesStmt(2, 1);
	uObj.setUsesStmt(3, 2);
	uObj.setUsesStmt(2, 3);
	uObj.setUsesStmt(3, 4);
	uObj.setUsesStmt(1, 5);
	uObj.setUsesStmt(4, 6);
	uObj.setUsesStmt(5, 7);

	AST aObject = *(*pkbObj).getAst();
	aObject.setStmtLine(aObject.createTNode(ASSIGNN, ""), 1);
	aObject.setStmtLine(aObject.createTNode(ASSIGNN, ""), 2);
	aObject.setStmtLine(aObject.createTNode(ASSIGNN, ""), 3);
	aObject.setStmtLine(aObject.createTNode(WHILEN, ""), 4);
	aObject.setStmtLine(aObject.createTNode(ASSIGNN, ""), 5);
	aObject.setStmtLine(aObject.createTNode(ASSIGNN, ""), 6);
	aObject.setStmtLine(aObject.createTNode(ASSIGNN, ""), 7);
}


CPPUNIT_TEST_SUITE_REGISTRATION(QueryEvaluatorTest);

// To test whether the Follow method is able to handle wildcards
void QueryEvaluatorTest::testFollowsTuple() {


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