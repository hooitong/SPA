#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <PKB.h>

class ParserEntityTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ParserEntityTest);
  CPPUNIT_TEST(testCFG);
  CPPUNIT_TEST(testAST);
  CPPUNIT_TEST(testVarTable);
  CPPUNIT_TEST(testProcTable);
  CPPUNIT_TEST_SUITE_END();

private:
  PKB* pkbTest;
  bool vectorContains(vector<string> container, string content);

public:
  void setUp();
  void tearDown();

  void testCFG();
  void testAST();
  void testVarTable();
  void testProcTable();
};