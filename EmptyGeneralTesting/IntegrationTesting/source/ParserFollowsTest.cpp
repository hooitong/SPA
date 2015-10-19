#include <cppunit/config/SourcePrefix.h>

#include "ParserFollowsTest.h"

void ParserFollowsTest::setUp() {
  fTest = PKB::getPKB()->getFollows();
}

void ParserFollowsTest::tearDown() {
  fTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserFollowsTest);

// Test whether the parser and PKB is able to capture all the Follows relationship
void ParserFollowsTest::testFollows() {
  // Correct Relationships

  CPPUNIT_ASSERT(fTest->isFollows(1, 2));
  CPPUNIT_ASSERT(fTest->isFollows(2, 3));
  CPPUNIT_ASSERT(fTest->isFollows(3, 4));
  CPPUNIT_ASSERT(fTest->isFollows(6, 7));
  CPPUNIT_ASSERT(fTest->isFollows(10, 11));
  CPPUNIT_ASSERT(fTest->isFollows(12, 13));
  CPPUNIT_ASSERT(fTest->isFollows(14, 15));
  CPPUNIT_ASSERT(fTest->isFollows(15, 16));
  CPPUNIT_ASSERT(fTest->isFollows(17, 20));
  CPPUNIT_ASSERT(fTest->isFollows(18, 19));
  CPPUNIT_ASSERT(fTest->isFollows(26, 27));
  CPPUNIT_ASSERT(fTest->isFollows(28, 29));
  CPPUNIT_ASSERT(fTest->isFollows(29, 30));
  CPPUNIT_ASSERT(fTest->isFollows(31, 34));
  CPPUNIT_ASSERT(fTest->isFollows(32, 33));

  // Incorrect Relationships
  CPPUNIT_ASSERT(!fTest->isFollows(4, 5));
  CPPUNIT_ASSERT(!fTest->isFollows(4, 22));
  CPPUNIT_ASSERT(!fTest->isFollows(5, 6));
  CPPUNIT_ASSERT(!fTest->isFollows(7, 8));
  CPPUNIT_ASSERT(!fTest->isFollows(23, 24));
  CPPUNIT_ASSERT(!fTest->isFollows(25, 26));
  CPPUNIT_ASSERT(!fTest->isFollows(27, 28));
  CPPUNIT_ASSERT(!fTest->isFollows(31, 32));
  CPPUNIT_ASSERT(!fTest->isFollows(36, 37));
}

// Test whether the parser and PKB is able to capture all the Follows* relationship
void ParserFollowsTest::testFollowsStar() {
  CPPUNIT_ASSERT(fTest->isFollowsStar(1, 2));
  CPPUNIT_ASSERT(fTest->isFollowsStar(2, 3));
  CPPUNIT_ASSERT(fTest->isFollowsStar(3, 4));
  CPPUNIT_ASSERT(fTest->isFollowsStar(6, 7));
  CPPUNIT_ASSERT(fTest->isFollowsStar(10, 11));
  CPPUNIT_ASSERT(fTest->isFollowsStar(12, 13));
  CPPUNIT_ASSERT(fTest->isFollowsStar(14, 15));
  CPPUNIT_ASSERT(fTest->isFollowsStar(15, 16));
  CPPUNIT_ASSERT(fTest->isFollowsStar(17, 20));
  CPPUNIT_ASSERT(fTest->isFollowsStar(18, 19));
  CPPUNIT_ASSERT(fTest->isFollowsStar(26, 27));
  CPPUNIT_ASSERT(fTest->isFollowsStar(28, 29));
  CPPUNIT_ASSERT(fTest->isFollowsStar(29, 30));
  CPPUNIT_ASSERT(fTest->isFollowsStar(31, 34));
  CPPUNIT_ASSERT(fTest->isFollowsStar(32, 33));

  // All Follows* Relationship in Procedures (exclude prev)
  CPPUNIT_ASSERT(fTest->isFollowsStar(1, 4));
  CPPUNIT_ASSERT(fTest->isFollowsStar(14, 16));
  CPPUNIT_ASSERT(fTest->isFollowsStar(28, 30));
}