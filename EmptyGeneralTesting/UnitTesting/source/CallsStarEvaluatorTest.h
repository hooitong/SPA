#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "CallsStarEvaluator.h"
#include "PKB.h"
#include "QueryTree.h"
#include <QNode.h>

class CallsStarEvaluatorTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CallsStarEvaluatorTest);
    CPPUNIT_TEST(testSynSyn);
    CPPUNIT_TEST(testSynAny);
    CPPUNIT_TEST(testSynConst);
    CPPUNIT_TEST(testAnySyn);
    CPPUNIT_TEST(testAnyAny);
    CPPUNIT_TEST(testAnyConst);
    CPPUNIT_TEST(testConstSyn);
    CPPUNIT_TEST(testConstAny);
    CPPUNIT_TEST(testConstConst);
    CPPUNIT_TEST_SUITE_END();

  private:
    PKB* pkbObj;
    QNode* createNode(string relationString, QNodeType type1, string s1, QNodeType type2, string s2);
    void cleanUp(QNode* node);


    map<PROCNAME, PROCINDEX> nameToIndex;

  public:
    void setUp();
    void tearDown();

    void testSynSyn();
    void testSynConst();
    void testSynAny();
    void testConstSyn();
    void testConstConst();
    void testConstAny();
    void testAnySyn();
    void testAnyConst();
    void testAnyAny();
};