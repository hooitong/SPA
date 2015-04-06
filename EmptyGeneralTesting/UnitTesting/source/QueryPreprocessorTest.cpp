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
	QueryTree* achieved = queryTest->parseQuery("stmt s1, s2; while w; assign a1,a2,a3; Select s1, s2, w, a1, a2, a3");
	QueryTree* expected = new QueryTree();
	QNode* expectedRoot = expected->createNode(QUERY,"");
	QNode* expectedResultList = expected->createNode(RESULTLIST,"");
	QNode* expectedSuchThatList = expected->createNode(SUCHTHATLIST,"");
	QNode* expectedPatternList = expected->createNode(PATTERNLIST,"");
	expected->setAsRoot(expectedRoot);
	expected->addChild(expectedRoot,expectedResultList);
	expected->addChild(expectedRoot,expectedSuchThatList);
	expected->addChild(expectedRoot,expectedPatternList);
	QNode* expectedResult1 = expected->createNode(STMTSYNONYM,"s1");
	QNode* expectedResult2 = expected->createNode(STMTSYNONYM,"s2");
	QNode* expectedResult3 = expected->createNode(WHILESYNONYM,"w");
	QNode* expectedResult4 = expected->createNode(ASSIGNSYNONYM,"a1");
	QNode* expectedResult5 = expected->createNode(ASSIGNSYNONYM,"a2");
	QNode* expectedResult6 = expected->createNode(ASSIGNSYNONYM,"a3");
	expected->addChild(expectedResultList,expectedResult1);
	expected->addChild(expectedResultList,expectedResult2);
	expected->addChild(expectedResultList,expectedResult3);
	expected->addChild(expectedResultList,expectedResult4);
	expected->addChild(expectedResultList,expectedResult5);
	expected->addChild(expectedResultList,expectedResult6);
	CPPUNIT_ASSERT(achieved->isEqual(expected));	
}
