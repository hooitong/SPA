#include <cppunit/config/SourcePrefix.h>

#include "ParserParentTest.h"

void ParserParentTest::setUp() {
	pTest = new Parent;
}

void ParserParentTest::tearDown() {
	delete pTest;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserParentTest);

// Test whether the parser and PKB is able to capture all the Parent relationship
void ParserParentTest::testParent() {

}

// Test whether the parser and PKB is able to capture all the Parent* relationship
void ParserParentTest::testParentStar() {

}