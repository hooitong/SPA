#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "ConstTable.h"
#include "PKB.h"

class ParserConstTableTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ParserConstTableTest);
  CPPUNIT_TEST(testConstTableItems);
  CPPUNIT_TEST_SUITE_END();

private:
  ConstTable* cTest;
  bool containConstant(vector<CONSTVALUE> *list, CONSTVALUE v);

public:
  void setUp();
  void tearDown();
  void testConstTableItems();
};