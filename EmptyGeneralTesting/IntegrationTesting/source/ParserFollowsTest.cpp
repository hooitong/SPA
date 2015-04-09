#include <cppunit/config/SourcePrefix.h>

#include "ParserFollowsTest.h"

void ParserFollowsTest::setUp() {
	fTest = new Follows;
}

void ParserFollowsTest::tearDown() {
	delete fTest;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserFollowsTest);

// Test whether the parser and PKB is able to capture all the Follows relationship
void ParserFollowsTest::testFollows() {

}

// Test whether the parser and PKB is able to capture all the Follows* relationship
void ParserFollowsTest::testFollowsStar() {

}