#include <cppunit/config/SourcePrefix.h>

#include "VarTableTest.h"

#include "VarTable.h"

void VarTableTest::setUp() {
  varTable = new VarTable;
}

void VarTableTest::tearDown() {
  delete varTable;
}

CPPUNIT_TEST_SUITE_REGISTRATION(VarTableTest);

void VarTableTest::testStoreRetrieveName() {
  VARINDEX indexOfX = varTable->insertVar("ab");
  CPPUNIT_ASSERT(indexOfX == 0);
  VARNAME name = varTable->getVarName(indexOfX);
  CPPUNIT_ASSERT(name == "ab");
}

void VarTableTest::testGetSize() {
  VARINDEX indexOfX = varTable->insertVar("x");
  VARINDEX indexOfY = varTable->insertVar("y");
  VARINDEX indexOfZ = varTable->insertVar("z");
  CPPUNIT_ASSERT(varTable->getSize() == 3);
  //vartable why the value is 3, should be 4 since its in the same run, the vartable instance should be the same
}

void VarTableTest::testGetAllVarIndex() {
  VARINDEX indexOfX = (*varTable).insertVar("x");
  VARINDEX indexOfY = (*varTable).insertVar("y");
  VARINDEX indexOfZ = (*varTable).insertVar("z");

  vector<VARINDEX> varIndexesLocal;
  varIndexesLocal.push_back(indexOfX);
  varIndexesLocal.push_back(indexOfY);
  varIndexesLocal.push_back(indexOfZ);

  CPPUNIT_ASSERT(varTable->getAllVarIndex() == varIndexesLocal);
}

void VarTableTest::testGetAllVarName() {
  VARINDEX indexOfX = (*varTable).insertVar("x");
  VARINDEX indexOfY = (*varTable).insertVar("y");
  VARINDEX indexOfZ = (*varTable).insertVar("z");

  vector<VARNAME> varNamesLocal;
  varNamesLocal.push_back("x");
  varNamesLocal.push_back("y");
  varNamesLocal.push_back("z");

  CPPUNIT_ASSERT(varTable->getAllVarName() == varNamesLocal);
}