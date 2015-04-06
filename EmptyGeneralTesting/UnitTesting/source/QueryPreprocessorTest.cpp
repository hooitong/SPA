#include <cppunit/config/SourcePrefix.h>

#include "QueryPreprocessorTest.h"
#include "QueryPreprocessor.h"
#include <string>

 void QueryPreprocessorTest::setUp(){
     QueryPreprocessor* queryTest = new QueryPreprocessor();
}

void QueryPreprocessorTest::tearDown(){
    delete queryTest;

}
CPPUNIT_TEST_SUITE_REGISTRATION(QueryPreprocessorTest);
void QueryPreprocessorTest::testParsing(){

	QueryTree* queryTree = (*queryTest).parseQuery("assign a; Select BOOLEAN such that Modifies(a, _)");
	//CPPUNIT_ASSERT(queryTree->getRoot()->getQType() == QUERY);
	//CPPUNIT_ASSERT(queryTree->getRoot()->getString() == "query");


}

void QueryPreprocessorTest::testNoCondition(){
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
