#include "ParserEntityTest.h"
#include <algorithm>

void ParserEntityTest::setUp() {
  pkbTest = PKB::getPKB();
}

void ParserEntityTest::tearDown() {
  pkbTest = nullptr;
}

bool ParserEntityTest::vectorContains(vector<string> container, string content) {
  return std::find(container.begin(), container.end(), content) != container.end();
}


CPPUNIT_TEST_SUITE_REGISTRATION(ParserEntityTest);

void ParserEntityTest::testAST() {
  AST *astTest = pkbTest->getAst();
  ProcTable *procTest = pkbTest->getProcTable();

  /* Ensure that all AST root is the same as the number of procedures */
  CPPUNIT_ASSERT(procTest->getAllTRoot().size() == pkbTest->getProcTable()->getSize());
}

void ParserEntityTest::testCFG() {
  CFG *cfgTest = pkbTest->getCfg();

  /* Ensure that every program line has a GNode representation */
  CPPUNIT_ASSERT(cfgTest->getAllGNodes().size() == 37);

  /* Check that the number of root node is equal to procedures */
  vector<GNode *> rootNodes = cfgTest->getAllRootNodes();
  CPPUNIT_ASSERT(rootNodes.size() == pkbTest->getProcTable()->getSize());
}

void ParserEntityTest::testVarTable() {
  VarTable *varTest = pkbTest->getVarTable();
  vector<VARINDEX> indexes = varTest->getAllVarIndex();
  vector<VARNAME> names = varTest->getAllVarName();

  /* Ensure that the variable table size is correct */
  CPPUNIT_ASSERT(varTest->getSize() == 20);

  /* Ensure that the variable namings are correct n */
  CPPUNIT_ASSERT(vectorContains(names, "i"));
  CPPUNIT_ASSERT(vectorContains(names, "b"));
  CPPUNIT_ASSERT(vectorContains(names, "c"));
  CPPUNIT_ASSERT(vectorContains(names, "a"));
  CPPUNIT_ASSERT(vectorContains(names, "beta"));
  CPPUNIT_ASSERT(vectorContains(names, "oSCar"));
  CPPUNIT_ASSERT(vectorContains(names, "tmp"));
  CPPUNIT_ASSERT(vectorContains(names, "I"));
  CPPUNIT_ASSERT(vectorContains(names, "k"));
  CPPUNIT_ASSERT(vectorContains(names, "j1k"));
  CPPUNIT_ASSERT(vectorContains(names, "chArlie"));
  CPPUNIT_ASSERT(vectorContains(names, "x"));
  CPPUNIT_ASSERT(vectorContains(names, "left"));
  CPPUNIT_ASSERT(vectorContains(names, "right"));
  CPPUNIT_ASSERT(vectorContains(names, "Romeo"));
  CPPUNIT_ASSERT(vectorContains(names, "width"));
  CPPUNIT_ASSERT(vectorContains(names, "Y1"));
  CPPUNIT_ASSERT(vectorContains(names, "x1"));
  CPPUNIT_ASSERT(vectorContains(names, "l"));

  /* Ensure that the number of indexes is equal to size */
  CPPUNIT_ASSERT(indexes.size() == 20);
}

void ParserEntityTest::testProcTable() {
  ProcTable *procTest = pkbTest->getProcTable();
  vector<PROCINDEX> indexes = procTest->getAllProcIndex();
  vector<PROCNAME> names = procTest->getAllProcName();

  /* Ensure that procedure table size is correct */
  CPPUNIT_ASSERT(procTest->getSize() == 3);

  /* Ensure that the procedure namings are correct */
  CPPUNIT_ASSERT(names[0] == "ABC");
  CPPUNIT_ASSERT(names[1] == "Second");
  CPPUNIT_ASSERT(names[2] == "Init");

  /* Ensure that the procedure indexes are correct and sequential */
  CPPUNIT_ASSERT(indexes[0] == 0);
  CPPUNIT_ASSERT(indexes[1] == 1);
  CPPUNIT_ASSERT(indexes[2] == 2);
}
