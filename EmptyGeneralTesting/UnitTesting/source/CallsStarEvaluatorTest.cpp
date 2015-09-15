#include <cppunit/config/SourcePrefix.h>

#include "CallsStarEvaluatorTest.h"
#include "CallsStarEvaluator.h"

void CallsStarEvaluatorTest::setUp() {
  pkbObj = new PKB();

  /*
    Setup based on:
    A -> B, C, D
    B -> C, F
    C -> <none>
    D -> E
    E -> <none>
    F -> <none>
    */
  ProcTable* table = pkbObj->getProcTable();
  nameToIndex["A"] = table->insertProc("A");
  nameToIndex["B"] = table->insertProc("B");
  nameToIndex["C"] = table->insertProc("C");
  nameToIndex["D"] = table->insertProc("D");
  nameToIndex["E"] = table->insertProc("E");
  nameToIndex["F"] = table->insertProc("F");

  Calls* calls = pkbObj->getCalls();
  calls->setCallsStar(nameToIndex["A"], nameToIndex["B"]);
  calls->setCallsStar(nameToIndex["A"], nameToIndex["C"]);
  calls->setCallsStar(nameToIndex["A"], nameToIndex["D"]);
  calls->setCallsStar(nameToIndex["A"], nameToIndex["E"]);
  calls->setCallsStar(nameToIndex["A"], nameToIndex["F"]);
  calls->setCallsStar(nameToIndex["B"], nameToIndex["C"]);
  calls->setCallsStar(nameToIndex["B"], nameToIndex["F"]);
  calls->setCallsStar(nameToIndex["D"], nameToIndex["E"]);
}

void CallsStarEvaluatorTest::tearDown() {
  delete pkbObj;
}

CPPUNIT_TEST_SUITE_REGISTRATION(CallsStarEvaluatorTest);

void CallsStarEvaluatorTest::testSynSyn() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", PROCEDURESYNONYM, "p1", PROCEDURESYNONYM, "p2");

  QueryResult result = eval.evaluate(node);

  vector<std::pair<PROCINDEX, PROCINDEX>> expected;
  expected.push_back(make_pair(nameToIndex["A"], nameToIndex["B"]));
  expected.push_back(make_pair(nameToIndex["A"], nameToIndex["C"]));
  expected.push_back(make_pair(nameToIndex["A"], nameToIndex["D"]));
  expected.push_back(make_pair(nameToIndex["A"], nameToIndex["E"]));
  expected.push_back(make_pair(nameToIndex["A"], nameToIndex["F"]));
  expected.push_back(make_pair(nameToIndex["B"], nameToIndex["C"]));
  expected.push_back(make_pair(nameToIndex["B"], nameToIndex["F"]));
  expected.push_back(make_pair(nameToIndex["D"], nameToIndex["E"]));

  QueryResult expectedResult(expected, "p1", "p2");

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testSynAny() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", PROCEDURESYNONYM, "p1", ANY, "");

  QueryResult result = eval.evaluate(node);

  vector<PROCINDEX> expected;
  expected.push_back(nameToIndex["A"]);
  expected.push_back(nameToIndex["B"]);
  expected.push_back(nameToIndex["D"]);

  QueryResult expectedResult(expected, "p1");

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testSynConst() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", PROCEDURESYNONYM, "p1", CONST, "C");

  QueryResult result = eval.evaluate(node);

  vector<PROCINDEX> expected;
  expected.push_back(nameToIndex["A"]);
  expected.push_back(nameToIndex["B"]);

  QueryResult expectedResult(expected, "p1");

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testAnySyn() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", ANY, "", PROCEDURESYNONYM, "p1");

  QueryResult result = eval.evaluate(node);

  vector<PROCINDEX> expected;
  expected.push_back(nameToIndex["B"]);
  expected.push_back(nameToIndex["C"]);
  expected.push_back(nameToIndex["D"]);
  expected.push_back(nameToIndex["E"]);
  expected.push_back(nameToIndex["F"]);

  QueryResult expectedResult(expected, "p1");

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testAnyAny() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", ANY, "", ANY, "");

  QueryResult result = eval.evaluate(node);

  QueryResult expectedResult(true);

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testAnyConst() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", ANY, "", CONST, "A");

  QueryResult result = eval.evaluate(node);

  QueryResult expectedResult(false);

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testConstSyn() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", CONST, "A", PROCEDURESYNONYM, "p1");

  QueryResult result = eval.evaluate(node);

  vector<PROCINDEX> expected;
  expected.push_back(nameToIndex["B"]);
  expected.push_back(nameToIndex["C"]);
  expected.push_back(nameToIndex["D"]);
  expected.push_back(nameToIndex["E"]);
  expected.push_back(nameToIndex["F"]);

  QueryResult expectedResult(expected, "p1");

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testConstAny() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", CONST, "A", ANY, "");

  QueryResult result = eval.evaluate(node);

  QueryResult expectedResult(true);

  CPPUNIT_ASSERT(result == expectedResult);
}

void CallsStarEvaluatorTest::testConstConst() {
  CallsStarEvaluator eval(pkbObj);

  QNode* node =
    createNode("Calls", CONST, "A", CONST, "F");

  QueryResult result = eval.evaluate(node);

  QueryResult expectedResult(true);

  CPPUNIT_ASSERT(result == expectedResult);
}

QNode* CallsStarEvaluatorTest::createNode(
  string relationString,
  QNodeType type1,
  string s1,
  QNodeType type2,
  string s2) {
  QNode* relation = new QNode(RELATION, relationString);
  QNode* arg1 = new QNode(type1, s1);
  QNode* arg2 = new QNode(type2, s2);

  relation->addChild(arg1);
  relation->addChild(arg2);
  return relation;
}

void CallsStarEvaluatorTest::cleanUp(QNode* node) {
  for (vector<QNode*>::size_type i = 0; i < node->getChildren().size(); i++) {
    cleanUp(node->getChildren()[i]);
  }
  delete node;
}