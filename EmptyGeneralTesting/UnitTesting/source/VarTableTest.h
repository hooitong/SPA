#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "VarTable.h"

class VarTableTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(VarTableTest);
  CPPUNIT_TEST(testStoreRetrieveName);
  CPPUNIT_TEST(testGetSize);
  CPPUNIT_TEST(testGetAllVarIndex);
  CPPUNIT_TEST(testGetAllVarName);
  CPPUNIT_TEST_SUITE_END();

private:
  VarTable* varTable;

public:
  void setUp();
  void tearDown();

  void testStoreRetrieveName();
  void testGetSize();
  void testGetAllVarIndex();
  void testGetAllVarName();
};
