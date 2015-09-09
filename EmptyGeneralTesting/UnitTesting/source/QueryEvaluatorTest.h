#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryEvaluator.h"
#include "PKB.h"
#include "QueryTree.h"
#include "QNode.h"

class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(QueryEvaluatorTest);
    CPPUNIT_TEST(testFollowsLeft);
    CPPUNIT_TEST(testFollowsRight);
    CPPUNIT_TEST(testFollowsBoth);
    CPPUNIT_TEST(testFollowsNone);
    CPPUNIT_TEST(testFollowsStarLeft);
    CPPUNIT_TEST(testFollowsStarRight);
    CPPUNIT_TEST(testFollowsStarBoth);
    CPPUNIT_TEST(testFollowsStarNone);
    CPPUNIT_TEST(testParentLeft);
    CPPUNIT_TEST(testParentRight);
    CPPUNIT_TEST(testParentBoth);
    CPPUNIT_TEST(testParentStarLeft);
    CPPUNIT_TEST(testParentStarRight);
    CPPUNIT_TEST(testParentStarBoth);
    CPPUNIT_TEST(testParentStarNone);
    CPPUNIT_TEST(testModifiesLeft);
    CPPUNIT_TEST(testModifiesRight);
    CPPUNIT_TEST(testModifiesBoth);
    CPPUNIT_TEST(testModifiesNone);
    CPPUNIT_TEST_SUITE_END();

  private:
    PKB* pkbObj;
    void setupTestData();
    QueryTree* createTree(
        QNodeType typeResult,
        string result,
        string relationString, QNodeType type1, string s1, QNodeType type2, string s2);

  public:
    void setUp();
    void tearDown();

    void testFollowsLeft();
    void testFollowsRight();
    void testFollowsBoth();
    void testFollowsNone();
    void testFollowsStarLeft();
    void testFollowsStarRight();
    void testFollowsStarBoth();
    void testFollowsStarNone();

    void testParentLeft();
    void testParentRight();
    void testParentBoth();
    void testParentNone();
    void testParentStarLeft();
    void testParentStarRight();
    void testParentStarBoth();
    void testParentStarNone();

    void testModifiesLeft();
    void testModifiesRight();
    void testModifiesBoth();
    void testModifiesNone();
};