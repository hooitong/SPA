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

void QueryPreprocessorTest::testOneConditionTwoSynonyms(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("while w; stmt s; Select w such that Follows(s,1)");
	QueryTree* expected = new QueryTree();
	QNode* expectedRoot = expected->createNode(QUERY,"");
	QNode* expectedResultList = expected->createNode(RESULTLIST,"");
	QNode* expectedSuchThatList = expected->createNode(SUCHTHATLIST,"");
	QNode* expectedPatternList = expected->createNode(PATTERNLIST,"");
	expected->setAsRoot(expectedRoot);
	expected->addChild(expectedRoot,expectedResultList);
	expected->addChild(expectedRoot,expectedSuchThatList);
	expected->addChild(expectedRoot,expectedPatternList);
	QNode* expectedResult = expected->createNode(WHILESYNONYM,"w");
	expected->addChild(expectedResultList,expectedResult);
	QNode* expectedSuchThat = expected->createNode(RELATION,"Follows");
	QNode* expectedSuchThatChild1 = expected->createNode(STMTSYNONYM,"s");
	QNode* expectedSuchThatChild2 = expected->createNode(CONST,"1");
	expected->addChild(expectedSuchThat,expectedSuchThatChild1);
	expected->addChild(expectedSuchThat,expectedSuchThatChild2);
	expected->addChild(expectedSuchThatList,expectedSuchThat);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}
void QueryPreprocessorTest::testPatternCondition(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(_,_)");
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
	QNode* expectedPatternNode = expected->createNode(PATTERN,"");
	QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
	QNode* expectedPatternChild2 = expected->createNode(ANY,"");
	QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_");
	expected->addChild(expectedPatternNode,expectedPatternChild1);
	expected->addChild(expectedPatternNode,expectedPatternChild2);
	expected->addChild(expectedPatternNode,expectedPatternChild3);
	expected->addChild(expectedPatternList,expectedPatternNode);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition1(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(_,_\"x\"_)");
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
	QNode* expectedPatternNode = expected->createNode(PATTERN,"");
	QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
	QNode* expectedPatternChild2 = expected->createNode(ANY,"");
	QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x_");
	expected->addChild(expectedPatternNode,expectedPatternChild1);
	expected->addChild(expectedPatternNode,expectedPatternChild2);
	expected->addChild(expectedPatternNode,expectedPatternChild3);
	expected->addChild(expectedPatternList,expectedPatternNode);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition2(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(_,_\"x+y\"_)");
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
	QNode* expectedPatternNode = expected->createNode(PATTERN,"");
	QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
	QNode* expectedPatternChild2 = expected->createNode(ANY,"");
	QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
	expected->addChild(expectedPatternNode,expectedPatternChild1);
	expected->addChild(expectedPatternNode,expectedPatternChild2);
	expected->addChild(expectedPatternNode,expectedPatternChild3);
	expected->addChild(expectedPatternList,expectedPatternNode);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition3(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(\"b\",_\"x+y\"_)");
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
	QNode* expectedPatternNode = expected->createNode(PATTERN,"");
	QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
	QNode* expectedPatternChild2 = expected->createNode(VAR,"b");
	QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
	expected->addChild(expectedPatternNode,expectedPatternChild1);
	expected->addChild(expectedPatternNode,expectedPatternChild2);
	expected->addChild(expectedPatternNode,expectedPatternChild3);
	expected->addChild(expectedPatternList,expectedPatternNode);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition4(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("assign a;variable b; Select a pattern a(b,_\"x+y\"_)");
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
	QNode* expectedPatternNode = expected->createNode(PATTERN,"");
	QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
	QNode* expectedPatternChild2 = expected->createNode(VARIABLESYNONYM,"b");
	QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
	expected->addChild(expectedPatternNode,expectedPatternChild1);
	expected->addChild(expectedPatternNode,expectedPatternChild2);
	expected->addChild(expectedPatternNode,expectedPatternChild3);
	expected->addChild(expectedPatternList,expectedPatternNode);
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}

