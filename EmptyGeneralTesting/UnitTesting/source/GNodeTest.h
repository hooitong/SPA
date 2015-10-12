#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "GNode.h"

class GNodeTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(GNodeTest);
  CPPUNIT_TEST(testGetAllPossibleEndNodes);
  CPPUNIT_TEST_SUITE_END();

private:

public:
  void setUp();
  void tearDown();

  void testGetAllPossibleEndNodes();
};
