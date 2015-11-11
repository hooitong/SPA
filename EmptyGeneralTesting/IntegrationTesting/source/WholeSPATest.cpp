#include <cppunit/config/SourcePrefix.h>

#include "WholeSPATest.h"

void WholeSPATest::setUp() {
}

void WholeSPATest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(WholeSPATest);

// Test whether the parser and PKB is able to capture all the Follows relationship
void WholeSPATest::test() {
	PKB::getPKB()->deletePKB();
	SPAFrontEnd::getInstance()->parseSource("whole.txt");

	std::list<std::string> results;
	string query = "stmt s; stmt s1; Select s1 such that Next*(s,s1) and Next*(s1,s)";

	QueryPreprocessor processor;
    QueryTree* tree = processor.parseQuery(query);

    QueryEvaluator evaluator(PKB::getPKB());

    results = evaluator.evaluate(tree);

	bool r = PKB::getPKB()->getNextBip()->isNext(42, 23);
  CPPUNIT_ASSERT(r);
}

