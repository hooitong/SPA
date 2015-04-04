#include <cppunit/config/SourcePrefix.h>

#include "FollowsTest.h"

void FollowsTest::setUp() {
    fTest = new Follows;
}

void FollowsTest::tearDown() {
    delete fTest;
}

CPPUNIT_TEST_SUITE_REGISTRATION(FollowsTest);

// Test whether the setFollows function works as intended.
void FollowsTest::testSet() {
    /* Set a few sample stmtLines */
    (*fTest).setFollows(1, 2);
    (*fTest).setFollows(2, 3);
    (*fTest).setFollows(3, 4);
    (*fTest).setFollows(6, 7);
    (*fTest).setFollows(7, 8);
}

// Test whether the setFollowsStar function works as intended.
void FollowsTest::testSetStar() {
    (*fTest).setFollowsStar(1, 2);
    (*fTest).setFollowsStar(2, 3);
    (*fTest).setFollowsStar(3, 4);
    (*fTest).setFollowsStar(6, 7);
    (*fTest).setFollowsStar(7, 8);

	(*fTest).setFollowsStar(1, 3);
	(*fTest).setFollowsStar(1, 4);
	(*fTest).setFollowsStar(2, 4);
	(*fTest).setFollowsStar(6, 8);
}

// Test whether the isFollows function works as intended.
void FollowsTest::testIsFollows() {
    testSet();

    /* Based on previous insertion, check the relationship whether it is valid */
    /* Should be valid for the following inputs */
    CPPUNIT_ASSERT((*fTest).isFollows(1, 2));
    CPPUNIT_ASSERT((*fTest).isFollows(2, 3));
    CPPUNIT_ASSERT((*fTest).isFollows(3, 4));
    CPPUNIT_ASSERT((*fTest).isFollows(6, 7));
    CPPUNIT_ASSERT((*fTest).isFollows(7, 8));

    /* Should be invalid for the following inputs */
    CPPUNIT_ASSERT(!(*fTest).isFollows(1, 3));
    CPPUNIT_ASSERT(!(*fTest).isFollows(1, 4));
    CPPUNIT_ASSERT(!(*fTest).isFollows(3, 7));
    CPPUNIT_ASSERT(!(*fTest).isFollows(10, 12));
}

// Test whether the isFollowsStar function works as intended.
void FollowsTest::testIsFollowsStar() {
    testSetStar();

    /* Based on previous insertion, check the relationship whether it is valid */
    /* Should be valid for the following inputs */
    CPPUNIT_ASSERT((*fTest).isFollowsStar(1, 2));
    CPPUNIT_ASSERT((*fTest).isFollowsStar(2, 3));
    CPPUNIT_ASSERT((*fTest).isFollowsStar(3, 4));
    CPPUNIT_ASSERT((*fTest).isFollowsStar(6, 7));
    CPPUNIT_ASSERT((*fTest).isFollowsStar(7, 8));
    CPPUNIT_ASSERT((*fTest).isFollowsStar(1, 3));
    CPPUNIT_ASSERT((*fTest).isFollowsStar(1, 4));

    /* Should be invalid for the following inputs */
    CPPUNIT_ASSERT(!(*fTest).isFollowsStar(10, 12));
    CPPUNIT_ASSERT(!(*fTest).isFollowsStar(3, 7));
}

// Test whether the testGetFollowsFrom function works as intended.
void FollowsTest::testGetFollowsFrom() {
    testSet();

    /* Valid inputs which should return the correct left sibling */
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(2) == 1);
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(3) == 2);
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(4) == 3);
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(8) == 7);

    /* Invalid inputs which should not return any left sibling */
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(-1) == -1);
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(5) == -1);
    CPPUNIT_ASSERT((*fTest).getFollowsFrom(10) == -1);
}

// Test whether the testGetFollowsFromStar function works as intended.
void FollowsTest::testGetFollowsFromStar() {
    testSetStar();
	
	/* Valid inputs which should return the correct left siblings */
    vector<STMTLINE> resultVector = (*fTest).getFollowsFromStar(2);
    CPPUNIT_ASSERT(resultVector[0] == 1);
    resultVector = (*fTest).getFollowsFromStar(3);
    CPPUNIT_ASSERT(resultVector[0] == 2);
    CPPUNIT_ASSERT(resultVector[1] == 1);
    resultVector = (*fTest).getFollowsFromStar(4);
    CPPUNIT_ASSERT(resultVector[0] == 3);
    CPPUNIT_ASSERT(resultVector[1] == 1);
    CPPUNIT_ASSERT(resultVector[2] == 2);
    resultVector = (*fTest).getFollowsFromStar(8);
    CPPUNIT_ASSERT(resultVector[0] == 7);
    CPPUNIT_ASSERT(resultVector[1] == 6);

    /* Invalid inputs which should not return any left siblings */
    resultVector = (*fTest).getFollowsFromStar(10);
    CPPUNIT_ASSERT(resultVector.empty());
}

// Test whether the getFollowedBy function works as intended.
void FollowsTest::testGetFollowedBy() {
    testSet();

    /* Valid inputs which should return the correct right sibling */
    CPPUNIT_ASSERT((*fTest).getFollowedBy(1) == 2);
    CPPUNIT_ASSERT((*fTest).getFollowedBy(2) == 3);
    CPPUNIT_ASSERT((*fTest).getFollowedBy(3) == 4);
    CPPUNIT_ASSERT((*fTest).getFollowedBy(6) == 7);
    CPPUNIT_ASSERT((*fTest).getFollowedBy(7) == 8);

    /* Invalid inputs which should not return any right sibling */
    CPPUNIT_ASSERT((*fTest).getFollowedBy(-1) == -1);
    CPPUNIT_ASSERT((*fTest).getFollowedBy(5) == -1);
    CPPUNIT_ASSERT((*fTest).getFollowedBy(9) == -1);
}

// Test whether the getFollowedByStar function works as intended.
void FollowsTest::testGetFollowedByStar() {
    testSetStar();

    /* Valid inputs which should return the correct right siblings */
    vector<STMTLINE> resultVector = (*fTest).getFollowedByStar(1);
    CPPUNIT_ASSERT(resultVector[0] == 2);
    CPPUNIT_ASSERT(resultVector[1] == 3);
    CPPUNIT_ASSERT(resultVector[2] == 4);
    resultVector = (*fTest).getFollowedByStar(6);
    CPPUNIT_ASSERT(resultVector[0] == 7);
    CPPUNIT_ASSERT(resultVector[1] == 8);

    /* Invalid inputs which should not return any right siblings* */
    resultVector = (*fTest).getFollowedByStar(4);
    CPPUNIT_ASSERT(resultVector.empty());
    resultVector = (*fTest).getFollowedByStar(-1);
    CPPUNIT_ASSERT(resultVector.empty());
}