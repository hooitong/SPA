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
    CPPUNIT_ASSERT(fTest->isFollows(5, 20));
    CPPUNIT_ASSERT(fTest->isFollows(6, 7));
    CPPUNIT_ASSERT(fTest->isFollows(7, 9));
    CPPUNIT_ASSERT(fTest->isFollows(9, 19));
    CPPUNIT_ASSERT(fTest->isFollows(10, 11));
    CPPUNIT_ASSERT(fTest->isFollows(12, 16));
    CPPUNIT_ASSERT(fTest->isFollows(16, 18));
    CPPUNIT_ASSERT(fTest->isFollows(13, 14));
    CPPUNIT_ASSERT(fTest->isFollows(14, 15));

    // Incorrect Relationships
    CPPUNIT_ASSERT(!fTest->isFollows(4, 20));
    CPPUNIT_ASSERT(!fTest->isFollows(19, 20));
    CPPUNIT_ASSERT(!fTest->isFollows(1, 3));
    CPPUNIT_ASSERT(!fTest->isFollows(1, 4));
    CPPUNIT_ASSERT(!fTest->isFollows(5, 19));
}

// Test whether the parser and PKB is able to capture all the Follows* relationship
void ParserFollowsTest::testFollowsStar() {
    // All Follows Relationship in Procedure ABC
    CPPUNIT_ASSERT(fTest->isFollowsStar(1, 2));
    CPPUNIT_ASSERT(fTest->isFollowsStar(2, 3));
    CPPUNIT_ASSERT(fTest->isFollowsStar(3, 4));
    CPPUNIT_ASSERT(fTest->isFollowsStar(5, 20));
    CPPUNIT_ASSERT(fTest->isFollowsStar(6, 7));
    CPPUNIT_ASSERT(fTest->isFollowsStar(7, 9));
    CPPUNIT_ASSERT(fTest->isFollowsStar(9, 19));
    CPPUNIT_ASSERT(fTest->isFollowsStar(10, 11));
    CPPUNIT_ASSERT(fTest->isFollowsStar(12, 16));
    CPPUNIT_ASSERT(fTest->isFollowsStar(16, 18));
    CPPUNIT_ASSERT(fTest->isFollowsStar(13, 14));
    CPPUNIT_ASSERT(fTest->isFollowsStar(14, 15));

    // All Follows* Relationship in Procedure ABC (exclude prev)
    CPPUNIT_ASSERT(fTest->isFollowsStar(1, 3));
    CPPUNIT_ASSERT(fTest->isFollowsStar(1, 4));
    CPPUNIT_ASSERT(fTest->isFollowsStar(2, 4));
    CPPUNIT_ASSERT(fTest->isFollowsStar(6, 9));
    CPPUNIT_ASSERT(fTest->isFollowsStar(6, 19));
    CPPUNIT_ASSERT(fTest->isFollowsStar(7, 19));
    CPPUNIT_ASSERT(fTest->isFollowsStar(12, 18));
    CPPUNIT_ASSERT(fTest->isFollowsStar(13, 15));
}