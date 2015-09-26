#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Modifies.h"
#include "PKB.h"

class ParserModifiesTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE(ParserModifiesTest);
  CPPUNIT_TEST(testModifiesStmt);
  CPPUNIT_TEST(testModifiesProc);
  CPPUNIT_TEST(testModifiesVarIndex);
  CPPUNIT_TEST(testModifiesProcIndex);
  CPPUNIT_TEST_SUITE_END();

private:
  Modifies* mTest;
  bool containStmtLine(vector<STMTLINE> *list, STMTLINE s);
  bool containProcIndex(vector<PROCINDEX> *list, PROCINDEX s);
  bool containVarIndex(vector<VARINDEX> *list, VARNAME v);
  bool matchSize(vector<VARINDEX> *list, int size);

public:
  void setUp();
  void tearDown();

  void testModifiesStmt();
  void testModifiesProc();
  void testModifiesVarIndex();
  void testModifiesProcIndex();
};