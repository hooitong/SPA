#include <cppunit/config/SourcePrefix.h>

#include "ParserCallsTest.h"

void ParserCallsTest::setUp() {
  cTest = PKB::getPKB()->getCalls();
}

void ParserCallsTest::tearDown() {
  cTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserCallsTest);

// Test whether the parser and PKB is able to capture all the Calls relationship
void ParserCallsTest::testCalls() {
  PROCINDEX ABC = PKB::getPKB()->getProcTable()->getProcIndex("ABC");
  PROCINDEX Second = PKB::getPKB()->getProcTable()->getProcIndex("Second");
  PROCINDEX Init = PKB::getPKB()->getProcTable()->getProcIndex("Init");

  // Correct Relationships
  CPPUNIT_ASSERT(cTest->isCall(ABC, Second));
  CPPUNIT_ASSERT(cTest->isCall(ABC, Init));
  CPPUNIT_ASSERT(cTest->isCall(Second, Init));

  // Incorrect Relationships
  CPPUNIT_ASSERT(!cTest->isCall(Second, Second));
  CPPUNIT_ASSERT(!cTest->isCall(Second, ABC));
  CPPUNIT_ASSERT(!cTest->isCall(Init, ABC));
  CPPUNIT_ASSERT(!cTest->isCall(Init, Second));
}

// Test whether the parser and PKB is able to capture all the Calls* relationship
void ParserCallsTest::testCallsStar() {
  PROCINDEX ABC = PKB::getPKB()->getProcTable()->getProcIndex("ABC");
  PROCINDEX Second = PKB::getPKB()->getProcTable()->getProcIndex("Second");
  PROCINDEX Init = PKB::getPKB()->getProcTable()->getProcIndex("Init");

  // Correct Relationships
  CPPUNIT_ASSERT(cTest->isCallStar(ABC, Second));
  CPPUNIT_ASSERT(cTest->isCallStar(ABC, Init));
  CPPUNIT_ASSERT(cTest->isCallStar(Second, Init));

  // Incorrect Relationships
  CPPUNIT_ASSERT(!cTest->isCallStar(Second, Second));
  CPPUNIT_ASSERT(!cTest->isCallStar(Second, ABC));
  CPPUNIT_ASSERT(!cTest->isCallStar(Init, ABC));
  CPPUNIT_ASSERT(!cTest->isCallStar(Init, Second));
}