#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Sibling.h"
#include "PKB.h"

class ParserSiblingTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ParserSiblingTest);
  CPPUNIT_TEST(testSibling);
  CPPUNIT_TEST(testGetSiblings);
  CPPUNIT_TEST_SUITE_END();

private:
  Sibling* sTest;

public:
  void setUp();
  void tearDown();

  void testSibling();
  void testGetSiblings();
};