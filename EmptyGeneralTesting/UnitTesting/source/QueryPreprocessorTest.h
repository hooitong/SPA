#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryPreprocessor.h"

class QueryPreprocessorTest : public CPPUNIT_NS::TestFixture{

	CPPUNIT_TEST_SUITE(QueryPreprocessorTest);
	CPPUNIT_TEST(testNoCondition);
	CPPUNIT_TEST(testNoConditionMoreComplex);
	CPPUNIT_TEST(testOneCondition);
	CPPUNIT_TEST(testOneConditionTwoSynonyms);
	CPPUNIT_TEST(testPatternCondition);
	CPPUNIT_TEST(testPatternCondition1);
	CPPUNIT_TEST(testPatternCondition2);
	CPPUNIT_TEST(testPatternCondition3);
	CPPUNIT_TEST(testPatternCondition4);
    CPPUNIT_TEST_SUITE_END();

  private:
	  QueryPreprocessor* queryTest;
  public:
    void setUp();
    void tearDown();
	void testNoCondition();
	void testNoConditionMoreComplex();
	void testOneCondition();
	void testOneConditionTwoSynonyms();
	void testPatternCondition();
	void testPatternCondition1();
	void testPatternCondition2();
	void testPatternCondition3();
	void testPatternCondition4();

};