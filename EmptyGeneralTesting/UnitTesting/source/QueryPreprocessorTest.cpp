#include <cppunit/config/SourcePrefix.h>

#include "QueryPreprocessorTest.h"
#include "QueryPreprocessor.h"
#include <string>

 void QueryPreprocessorTest::setUp(){
     queryTest = new QueryPreprocessor();
}

void QueryPreprocessorTest::tearDown(){
    delete queryTest;

}
CPPUNIT_TEST_SUITE_REGISTRATION(QueryPreprocessorTest);
void QueryPreprocessorTest::testParsing(){
	queryTest = new QueryPreprocessor();
	QueryTree* queryTree = queryTest->parseQuery("assign a; Select BOOLEAN such that Modifies(a, _)");
	//CPPUNIT_ASSERT(queryTree->getRoot()->getQType() == QUERY);
	//CPPUNIT_ASSERT(queryTree->getRoot()->getString() == "query");

}

void QueryPreprocessorTest::testNoCondition(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("stmt s; Select s");
	QueryTree* expected = new QueryTree();
	QNode* expectedRoot = expected->createNode(QUERY,"");
	QNode* expectedResultList = expected->createNode(RESULTLIST,"");
	QNode* expectedSuchThatList = expected->createNode(SUCHTHATLIST,"");
	QNode* expectedPatternList = expected->createNode(PATTERNLIST,"");
	expected->setAsRoot(expectedRoot);
	expected->addChild(expectedRoot,expectedResultList);
	expected->addChild(expectedRoot,expectedSuchThatList);
	expected->addChild(expectedRoot,expectedPatternList);
	QNode* expectedResult = expected->createNode(STMTSYNONYM,"s");
	expected->addChild(expectedResultList,expectedResult);
	CPPUNIT_ASSERT(achieved->isEqual(expected));	
}

void QueryPreprocessorTest::testNoConditionMoreComplex(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("stmt s1, s2; while w; assign a1, a2, a3; Select a2");
	QueryTree* expected = new QueryTree();
	QNode* expectedRoot = expected->createNode(QUERY,"");
	QNode* expectedResultList = expected->createNode(RESULTLIST,"");
	QNode* expectedSuchThatList = expected->createNode(SUCHTHATLIST,"");
	QNode* expectedPatternList = expected->createNode(PATTERNLIST,"");
	expected->setAsRoot(expectedRoot);
	expected->addChild(expectedRoot,expectedResultList);
	expected->addChild(expectedRoot,expectedSuchThatList);
	expected->addChild(expectedRoot,expectedPatternList);
	QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a2");
	expected->addChild(expectedResultList,expectedResult);
	CPPUNIT_ASSERT(achieved->isEqual(expected));	
}

void QueryPreprocessorTest::testOneCondition(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("assign a; Select a such that Follows(a,2)");
	QueryTree* expected = new QueryTree();
	QNode* expectedRoot = expected->createNode(QUERY,"");
	QNode* expectedResultList = expected->createNode(RESULTLIST,"");
	QNode* expectedSuchThatList = expected->createNode(SUCHTHATLIST,"");
	QNode* expectedPatternList = expected->createNode(PATTERNLIST,"");
	expected->setAsRoot(expectedRoot);
	expected->addChild(expectedRoot,expectedResultList);
	expected->addChild(expectedRoot,expectedSuchThatList);
	expected->addChild(expectedRoot,expectedPatternList);
	QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
	expected->addChild(expectedResultList,expectedResult);
	QNode* expectedSuchThat = expected->createNode(RELATION,"Follows");
	QNode* expectedSuchThatChild1 = expected->createNode(ASSIGNSYNONYM,"a");
	QNode* expectedSuchThatChild2 = expected->createNode(CONST,"2");
	expected->addChild(expectedSuchThat,expectedSuchThatChild1);
	expected->addChild(expectedSuchThat,expectedSuchThatChild2);
	expected->addChild(expectedSuchThatList,expectedSuchThat);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}
