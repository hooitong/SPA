#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryPreprocessor.h"

class QueryPreprocessorTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(QueryPreprocessorTest);
  CPPUNIT_TEST(testNoCondition);
  CPPUNIT_TEST(testNoConditionMoreComplex);
  CPPUNIT_TEST(testOneCondition);
  CPPUNIT_TEST(testOneConditionTwoSynonyms);
  CPPUNIT_TEST(testRepeatCondition);
  CPPUNIT_TEST(testPatternCondition);
  CPPUNIT_TEST(testPatternCondition1);
  CPPUNIT_TEST(testPatternCondition2);
  CPPUNIT_TEST(testPatternCondition3);
  CPPUNIT_TEST(testPatternCondition4);
  CPPUNIT_TEST(testPatternCondition5);
  CPPUNIT_TEST(testSuchThatCondition);
  CPPUNIT_TEST(testSuchThatCondition1);
  CPPUNIT_TEST(testSuchThatCondition2);
  CPPUNIT_TEST(testSuchThatCondition3);
  CPPUNIT_TEST(testSuchThatCondition4);
  CPPUNIT_TEST(testSuchThatCondition5);
  CPPUNIT_TEST(testSuchThatCondition6);
  CPPUNIT_TEST(testSuchThatCondition7);
  CPPUNIT_TEST(testWithCondition);
  CPPUNIT_TEST(testWithCondition1);
  CPPUNIT_TEST(testProgLine);
  CPPUNIT_TEST(testInvalidQuery);
  CPPUNIT_TEST(testPatternInvalid);
  CPPUNIT_TEST(testPatternInvalid2);
  CPPUNIT_TEST(testPatternInvalid3);
  CPPUNIT_TEST(testPatternInvalid4);
  CPPUNIT_TEST(testPatternInvalid5);
  CPPUNIT_TEST(testUses);
  CPPUNIT_TEST(testUsesInvalid);
  CPPUNIT_TEST(testInvalidNotDeclared);
  CPPUNIT_TEST(testInvalidNotDeclared2);
  CPPUNIT_TEST(testMultipleReturn);
  CPPUNIT_TEST(testMultipleReturnAndSuchThat);
  CPPUNIT_TEST(testMultipleReturnAndMultipleSuchThat);
  CPPUNIT_TEST(testMultiplePatternAndMultipleSuchThat);
  CPPUNIT_TEST(testMultipleReturnAndPatternAndSuchThat);
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
  void testRepeatCondition();
  void testPatternCondition();
  void testPatternCondition1();
  void testPatternCondition2();
  void testPatternCondition3();
  void testPatternCondition4();
  void testPatternCondition5();
  void testSuchThatCondition();
  void testSuchThatCondition1();
  void testSuchThatCondition2();
  void testSuchThatCondition3();
  void testSuchThatCondition4();
  void testSuchThatCondition5();
  void testSuchThatCondition6();
  void testSuchThatCondition7();
  void testWithCondition();
  void testWithCondition1();
  void testProgLine();
  void testPatternInvalid();
  void testPatternInvalid2();
  void testPatternInvalid3();
  void testPatternInvalid4();
  void testPatternInvalid5();
  void testUses();
  void testUsesInvalid();
  void testInvalidQuery();
  void testInvalidNotDeclared();
  void testInvalidNotDeclared2();
  void testMultipleReturn();
  void testMultipleReturnAndSuchThat();
  void testMultipleReturnAndMultipleSuchThat();
  void testMultiplePatternAndMultipleSuchThat();
  void testMultipleReturnAndPatternAndSuchThat();
};

