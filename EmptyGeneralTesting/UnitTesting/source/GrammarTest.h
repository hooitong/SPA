#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Grammar.h"

class GrammarTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(GrammarTest);
  CPPUNIT_TEST(testSetup);
  CPPUNIT_TEST(testConvert);
  CPPUNIT_TEST_SUITE_END();

private:

public:
  void setUp();
  void tearDown();

  void testSetup();
  void testConvert();
};
