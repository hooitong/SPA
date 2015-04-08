#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryPreprocessor.h"

class QueryPreprocessorTest : public CPPUNIT_NS::TestFixture{

	CPPUNIT_TEST_SUITE(QueryPreprocessorTest);
    /*CPPUNIT_TEST(testParsing);
	CPPUNIT_TEST(testNoCondition);
	CPPUNIT_TEST(testNoConditionMoreComplex);
	CPPUNIT_TEST(testOneCondition);
	CPPUNIT_TEST(testOneConditionTwoSynonyms);
	CPPUNIT_TEST(testRelationCondition);
	CPPUNIT_TEST(testPatternCondition);
	CPPUNIT_TEST(testPatternCondition1);
	CPPUNIT_TEST(testPatternCondition2);
	CPPUNIT_TEST(testPatternCondition3);
	CPPUNIT_TEST(testPatternCondition4);*/
	CPPUNIT_TEST(testRelationCondition);
	/*CPPUNIT_TEST(testRelationCondition1);
	CPPUNIT_TEST(testRelationCondition2);
	CPPUNIT_TEST(testRelationCondition3);
	CPPUNIT_TEST(testRelationCondition4);*/
    CPPUNIT_TEST_SUITE_END();

  private:
	  QueryPreprocessor* queryTest;
  public:
    void setUp();
    void tearDown();
	void testParsing();
	void testNoCondition();
	void testNoConditionMoreComplex();
	void testOneCondition();
	void testOneConditionTwoSynonyms();
	void testPatternCondition();
	void testPatternCondition1();
	void testPatternCondition2();
	void testPatternCondition3();
	void testPatternCondition4();
	void testRelationCondition();
	void testRelationCondition1();
	void testRelationCondition2();
	void testRelationCondition3();
	void testRelationCondition4();
};