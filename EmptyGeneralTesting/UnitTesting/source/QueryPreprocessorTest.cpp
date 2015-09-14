#include <cppunit/config/SourcePrefix.h>

#include "QueryPreprocessorTest.h"

#include <string>

#include "QueryPreprocessor.h"


void QueryPreprocessorTest::setUp() {
    queryTest = new QueryPreprocessor();
}

void QueryPreprocessorTest::tearDown() {
    delete queryTest;

}
CPPUNIT_TEST_SUITE_REGISTRATION(QueryPreprocessorTest);


void QueryPreprocessorTest::testNoCondition() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("stmt s; Select s");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(STMTSYNONYM,"s");
    expected->addChild(expectedResultList,expectedResult);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testNoConditionMoreComplex() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("stmt s1, s2; while w; assign a1, a2, a3; Select a2");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a2");
    expected->addChild(expectedResultList,expectedResult);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testOneCondition() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; Select a such that Follows(a,2)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedSuchThat = expected->createNode(RELATION,"Follows");
    QNode* expectedSuchThatChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedSuchThatChild2 = expected->createNode(CONST,"2");
    expected->addChild(expectedSuchThat,expectedSuchThatChild1);
    expected->addChild(expectedSuchThat,expectedSuchThatChild2);
    expected->addChild(expectedConditionList,expectedSuchThat);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testOneConditionTwoSynonyms() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("while w; stmt s; Select w such that Follows(s,1)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(WHILESYNONYM,"w");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedSuchThat = expected->createNode(RELATION,"Follows");
    QNode* expectedSuchThatChild1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild2 = expected->createNode(CONST,"1");
    expected->addChild(expectedSuchThat,expectedSuchThatChild1);
    expected->addChild(expectedSuchThat,expectedSuchThatChild2);
    expected->addChild(expectedConditionList,expectedSuchThat);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testRepeatCondition() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("while w; stmt s; while w1; Select <w,w1> such that Follows(s,1)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(WHILESYNONYM,"w");
	QNode* expectedResult1 = expected->createNode(WHILESYNONYM,"w1");
    expected->addChild(expectedResultList,expectedResult);
	expected->addChild(expectedResultList,expectedResult1);
    QNode* expectedSuchThat = expected->createNode(RELATION,"Follows");
    QNode* expectedSuchThatChild1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild2 = expected->createNode(CONST,"1");
    expected->addChild(expectedSuchThat,expectedSuchThatChild1);
    expected->addChild(expectedSuchThat,expectedSuchThatChild2);
    expected->addChild(expectedConditionList,expectedSuchThat);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}
void QueryPreprocessorTest::testPatternCondition() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(_,_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(ANY,"");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition1() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; stmt s; Select a such that Follows(s,1) pattern a(_,_\"x\"_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);

    QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(ANY,"");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);

    QNode* expectedSuchThat = expected->createNode(RELATION,"Follows");
    QNode* expectedSuchThatChild1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild2 = expected->createNode(CONST,"1");
    expected->addChild(expectedSuchThat,expectedSuchThatChild1);
    expected->addChild(expectedSuchThat,expectedSuchThatChild2);
    expected->addChild(expectedConditionList,expectedSuchThat);

    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition2() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(_,_\"x+y\"_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(ANY,"");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition3() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a(\"b\",_\"x+y\"_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(VAR,"b");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition4() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;variable b; Select a pattern a(b,_\"x+y\"_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(VARIABLESYNONYM,"b");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testPatternCondition5() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; Select a pattern a ( _ , _\"delta + 1 + width + Romeo\"_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult = expected->createNode(ASSIGNSYNONYM,"a");
    expected->addChild(expectedResultList,expectedResult);
    QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(ANY,"");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_delta + 1 + width + Romeo_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testProgLine() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("prog_line n; assign a;   Select   n such that Uses(a, \"tmp\")");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);

    QNode* expectedResult = expected->createNode(PROGLINESYNONYM,"n");
    expected->addChild(expectedResultList,expectedResult);

    QNode* expectedUsesNode = expected->createNode(RELATION,"Uses");
    QNode* expectedUsesChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedUsesChild2 = expected->createNode(VAR,"tmp");
    expected->addChild(expectedUsesNode,expectedUsesChild1);
    expected->addChild(expectedUsesNode,expectedUsesChild2);
    expected->addChild(expectedConditionList,expectedUsesNode);

    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testUses(){
	queryTest = new QueryPreprocessor();
	QueryTree* achieved = queryTest->parseQuery("stmt s; Select s such that Uses(s,_)");
	CPPUNIT_ASSERT(achieved != NULL);
	QueryTree* expected = new QueryTree();
	QNode* expectedRoot = expected->createNode(QUERY,"");
	QNode* expectedResultList = expected->createNode(RESULTLIST,"");
	QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
	expected->setAsRoot(expectedRoot);
	expected->addChild(expectedRoot,expectedResultList);
	expected->addChild(expectedRoot,expectedConditionList);

	QNode* expectedResult = expected->createNode(STMTSYNONYM,"s");
	expected->addChild(expectedResultList,expectedResult);

	QNode* expectedUsesNode = expected->createNode(RELATION,"Uses");
	QNode* expectedUsesChild1 = expected->createNode(STMTSYNONYM,"s");
	QNode* expectedUsesChild2 = expected->createNode(ANY,"");
	expected->addChild(expectedUsesNode,expectedUsesChild1);
	expected->addChild(expectedUsesNode,expectedUsesChild2);
	expected->addChild(expectedConditionList,expectedUsesNode);
	
	CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testUsesInvalid() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("stmt s; Select s such that Uses(_,s)");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testInvalidQuery() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("Select");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testPatternInvalid() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a; Select a Pattern a(_,_)");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testPatternInvalid2() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;stmt s; Select a pattern a (, \"_\")");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testPatternInvalid3() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;stmt s; Select a pattern a (_, \"_delta + l + width + Romeo\")");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testPatternInvalid4() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;stmt s; Select a pattern a(,\"delta\"__)");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testPatternInvalid5() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;stmt s; Select a pattern a(_,\"delta\"_)");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testInvalidNotDeclared() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("Select n such that Uses(a, \"tmp\") ");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testInvalidNotDeclared2() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("prog_line n; Select n such that Uses(a, \"tmp\") ");
    CPPUNIT_ASSERT(achieved == NULL);
}

void QueryPreprocessorTest::testMultipleReturn() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("stmt s1, s2; Select <s1,s2>");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);
    QNode* expectedResult1 = expected->createNode(STMTSYNONYM,"s1");
    QNode* expectedResult2 = expected->createNode(STMTSYNONYM,"s2");
    expected->addChild(expectedResultList,expectedResult1);
    expected->addChild(expectedResultList,expectedResult2);
    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testMultipleReturnAndSuchThat() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("stmt s; variable x; Select <s,x> such that Modifies(s,x)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);

    QNode* expectedResult1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedResult2 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedResultList,expectedResult1);
    expected->addChild(expectedResultList,expectedResult2);

    QNode* expectedSuchThat = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild2 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedSuchThat,expectedSuchThatChild1);
    expected->addChild(expectedSuchThat,expectedSuchThatChild2);
    expected->addChild(expectedConditionList,expectedSuchThat);

    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testMultipleReturnAndMultipleSuchThat() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("stmt s; variable x; Select <s,x> such that Modifies(s,x) and Modifies(s,\"x\")");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);

    QNode* expectedResult1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedResult2 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedResultList,expectedResult1);
    expected->addChild(expectedResultList,expectedResult2);

    QNode* expectedSuchThat1 = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild11 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild12 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedSuchThat1,expectedSuchThatChild11);
    expected->addChild(expectedSuchThat1,expectedSuchThatChild12);
    QNode* expectedSuchThat2 = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild21 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild22 = expected->createNode(VAR,"x");
    expected->addChild(expectedSuchThat2,expectedSuchThatChild21);
    expected->addChild(expectedSuchThat2,expectedSuchThatChild22);
    expected->addChild(expectedConditionList,expectedSuchThat1);
    expected->addChild(expectedConditionList,expectedSuchThat2);

    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testMultiplePatternAndMultipleSuchThat() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;variable x,b; stmt s; Select <s,x> such that Modifies(s,x) and Modifies(s,\"x\") pattern a(b,_\"x+y\"_)");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);

    QNode* expectedResult1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedResult2 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedResultList,expectedResult1);
    expected->addChild(expectedResultList,expectedResult2);

    QNode* expectedSuchThat1 = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild11 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild12 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedSuchThat1,expectedSuchThatChild11);
    expected->addChild(expectedSuchThat1,expectedSuchThatChild12);

    QNode* expectedSuchThat2 = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild21 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild22 = expected->createNode(VAR,"x");
	expected->addChild(expectedSuchThat2,expectedSuchThatChild21);
    expected->addChild(expectedSuchThat2,expectedSuchThatChild22);

    expected->addChild(expectedConditionList,expectedSuchThat1);
    expected->addChild(expectedConditionList,expectedSuchThat2);

	QNode* expectedPatternNode = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild1 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild2 = expected->createNode(VARIABLESYNONYM,"b");
    QNode* expectedPatternChild3 = expected->createNode(EXPRESSION,"_x+y_");
    expected->addChild(expectedPatternNode,expectedPatternChild1);
    expected->addChild(expectedPatternNode,expectedPatternChild2);
    expected->addChild(expectedPatternNode,expectedPatternChild3);
    expected->addChild(expectedConditionList,expectedPatternNode);


    CPPUNIT_ASSERT(achieved->isEqual(expected));
}

void QueryPreprocessorTest::testMultipleReturnAndPatternAndSuchThat() {
    queryTest = new QueryPreprocessor();
    QueryTree* achieved = queryTest->parseQuery("assign a;variable x; stmt s; Select <s,x> such that Modifies(s,x) and Modifies(s,\"x\") pattern a(\"b\",_\"x+y\"_) and a(_,\"(x+y)*z\")");
    CPPUNIT_ASSERT(achieved != NULL);
    QueryTree* expected = new QueryTree();
    QNode* expectedRoot = expected->createNode(QUERY,"");
    QNode* expectedResultList = expected->createNode(RESULTLIST,"");
    QNode* expectedConditionList = expected->createNode(CONDITIONLIST,"");
    expected->setAsRoot(expectedRoot);
    expected->addChild(expectedRoot,expectedResultList);
    expected->addChild(expectedRoot,expectedConditionList);

    QNode* expectedResult1 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedResult2 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedResultList,expectedResult1);
    expected->addChild(expectedResultList,expectedResult2);

    QNode* expectedSuchThat1 = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild11 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild12 = expected->createNode(VARIABLESYNONYM,"x");
    expected->addChild(expectedSuchThat1,expectedSuchThatChild11);
    expected->addChild(expectedSuchThat1,expectedSuchThatChild12);

    QNode* expectedSuchThat2 = expected->createNode(RELATION,"Modifies");
    QNode* expectedSuchThatChild21 = expected->createNode(STMTSYNONYM,"s");
    QNode* expectedSuchThatChild22 = expected->createNode(VAR,"x");
    expected->addChild(expectedSuchThat2,expectedSuchThatChild21);
    expected->addChild(expectedSuchThat2,expectedSuchThatChild22);

	expected->addChild(expectedConditionList,expectedSuchThat1);
    expected->addChild(expectedConditionList,expectedSuchThat2);

	QNode* expectedPatternNode1 = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild11 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild12 = expected->createNode(VAR,"b");
    QNode* expectedPatternChild13 = expected->createNode(EXPRESSION,"_x+y_");
    expected->addChild(expectedPatternNode1,expectedPatternChild11);
    expected->addChild(expectedPatternNode1,expectedPatternChild12);
    expected->addChild(expectedPatternNode1,expectedPatternChild13);
    expected->addChild(expectedConditionList,expectedPatternNode1);

	QNode* expectedPatternNode2 = expected->createNode(PATTERN,"");
    QNode* expectedPatternChild21 = expected->createNode(ASSIGNSYNONYM,"a");
    QNode* expectedPatternChild22 = expected->createNode(ANY,"");
    QNode* expectedPatternChild23 = expected->createNode(EXPRESSION,"(x+y)*z");
    expected->addChild(expectedPatternNode2,expectedPatternChild21);
    expected->addChild(expectedPatternNode2,expectedPatternChild22);
    expected->addChild(expectedPatternNode2,expectedPatternChild23);
    expected->addChild(expectedConditionList,expectedPatternNode2);




    CPPUNIT_ASSERT(achieved->isEqual(expected));
}


