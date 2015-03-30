#pragma once

#include <cppunit/extensions/HelperMacros.h>

class QueryResultTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(QueryResultTest);
    CPPUNIT_TEST(testEqual);
    CPPUNIT_TEST(testEqualReorder);
    CPPUNIT_TEST(testDifferent);
    CPPUNIT_TEST(testFirstEmptySynonym);
    CPPUNIT_TEST(testSecondEmptySynonym);
    CPPUNIT_TEST(testMultipleMerge);
	CPPUNIT_TEST(testFilter);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void testEqual();
    void testEqualReorder();
    void testDifferent();
    void testFirstEmptySynonym();
    void testSecondEmptySynonym();
    void testMultipleMerge();
	void testFilter();
}
;