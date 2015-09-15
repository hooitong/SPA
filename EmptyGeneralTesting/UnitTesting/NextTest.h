#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Next.h"

class NextTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(NextTest);
  CPPUNIT_TEST(testSetNext);
  CPPUNIT_TEST(testSetNextStar);
  CPPUNIT_TEST(testIsNext);
  CPPUNIT_TEST(testIsNextStar);
  CPPUNIT_TEST(testGetBefore);
  CPPUNIT_TEST(testGetBeforeStar);
  CPPUNIT_TEST(testGetNext);
  CPPUNIT_TEST(testGetNextStar);
  CPPUNIT_TEST_SUITE_END();

private:
  Next* next;

public:
  void setUp();
  void tearDown();

  void testSetNext();
  void testSetNextStar();
  void testIsNext();
  void testIsNextStar();
  void testGetBefore();
  void testGetBeforeStar();
  void testGetNext();
  void testGetNextStar();
};
