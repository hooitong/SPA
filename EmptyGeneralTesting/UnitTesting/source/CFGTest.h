#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "CFG.h"

class CFGTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(CFGTest);
  CPPUNIT_TEST(testInsert);
  CPPUNIT_TEST(testGetAllToStmts);
  CPPUNIT_TEST_SUITE_END();

private:

public:
  void setUp();
  void tearDown();

  void testInsert();
  void testGetAllToStmts();
};
