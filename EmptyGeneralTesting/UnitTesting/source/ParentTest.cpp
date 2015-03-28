#include <cppunit/config/SourcePrefix.h>
#include "ParentTest.h"


void ParentTest::setUp() {
    pTest = new Parent;
}

void ParentTest::tearDown() {
    delete pTest;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParentTest);

// Test whether the setParent function works as intended.
void ParentTest::testSet() {
    /* Set a few sample stmtLines */
    (*pTest).setParent(1, 2);
    (*pTest).setParent(2, 3);

    /* The returned value of getParent should be equivalent */
    STMTLINE result = (*pTest).getParent(2);
    CPPUNIT_ASSERT(result == 1);
    result = (*pTest).getParent(3);
    CPPUNIT_ASSERT(result == 2);

    /* Test for non-existent relationships */
    result = (*pTest).getParent(6);
    CPPUNIT_ASSERT(result == -1);
}

// Test whether the setParentStar function works as intended.
void ParentTest::testSetStar() {
    /* Set a few sample stmtLines */
    (*pTest).setParentStar(4, 8);
    (*pTest).setParentStar(1, 8);
    (*pTest).setParentStar(4, 5);

    /* The returned value of getParentStar should be correct */
    vector<STMTLINE> resultVector = (*pTest).getParentStar(8);
    CPPUNIT_ASSERT(resultVector[0] == 4);
    CPPUNIT_ASSERT(resultVector[1] == 1);

    /* The returned value of getChildOfStar should be correct */
    resultVector = (*pTest).getChildOfStar(4);
    CPPUNIT_ASSERT(resultVector[0] == 8);
    CPPUNIT_ASSERT(resultVector[1] == 5);
}

// Test whether the isParent function works as intended.
void ParentTest::testIsParent() {
    testSet();
    testSetStar();

    /* Based on previous insertion, check the relationship whether it is valid */
    /* Should be valid for the following inputs */
    CPPUNIT_ASSERT((*pTest).isParent(1, 2));
    CPPUNIT_ASSERT((*pTest).isParent(2, 3));

    /* Should be invalid for the following inputs */
    CPPUNIT_ASSERT(!(*pTest).isParent(4, 8));
    CPPUNIT_ASSERT(!(*pTest).isParent(1, 8));
    CPPUNIT_ASSERT(!(*pTest).isParent(4, 5));
    CPPUNIT_ASSERT(!(*pTest).isParent(10, 12));
}

// Test whether the isParentStar function works as intended.
void ParentTest::testIsParentStar() {
    testSet();
    testSetStar();

    /* Based on previous insertion, check the relationship whether it is valid */
    /* Should be valid for the following inputs */
    CPPUNIT_ASSERT((*pTest).isParentStar(1, 2));
    CPPUNIT_ASSERT((*pTest).isParentStar(2, 3));
    CPPUNIT_ASSERT((*pTest).isParentStar(4, 8));
    CPPUNIT_ASSERT((*pTest).isParentStar(1, 8));
    CPPUNIT_ASSERT((*pTest).isParentStar(4, 5));

    /* Should be invalid for the following inputs */
    CPPUNIT_ASSERT(!(*pTest).isParentStar(10, 12));
}

// Test whether the getParent function works as intended.
void ParentTest::testGetParent() {
    testSet();
    testSetStar();

    /* Valid inputs which should return the correct parents */
    CPPUNIT_ASSERT((*pTest).getParent(2) == 1);
    CPPUNIT_ASSERT((*pTest).getParent(3) == 2);

    /* Invalid inputs which should not return any parent */
    CPPUNIT_ASSERT((*pTest).getParent(5) == -1);
    CPPUNIT_ASSERT((*pTest).getParent(8) == -1);
    CPPUNIT_ASSERT((*pTest).getParent(10) == -1);
}

// Test whether the getParentStar function works as intended.
void ParentTest::testGetParentStar() {
    testSet();
    testSetStar();

    /* Valid inputs which should return the correct parent* */
    vector<STMTLINE> resultVector = (*pTest).getParentStar(2);
    CPPUNIT_ASSERT(resultVector[0] == 1);
    resultVector = (*pTest).getParentStar(3);
    CPPUNIT_ASSERT(resultVector[0] == 2);
    resultVector = (*pTest).getParentStar(8);
    CPPUNIT_ASSERT(resultVector[0] == 4);
    CPPUNIT_ASSERT(resultVector[1] == 1);
    resultVector = (*pTest).getParentStar(5);
    CPPUNIT_ASSERT(resultVector[0] == 4);

    /* Invalid inputs which should not return any parent* */
    resultVector = (*pTest).getParentStar(10);
    CPPUNIT_ASSERT(resultVector.empty());
}

// Test whether the getChildOf function works as intended.
void ParentTest::testGetChildOf() {
    testSet();
    testSetStar();

    /* Valid inputs which should return the correct child */
    vector<STMTLINE> resultVector = (*pTest).getChildOf(1);
    CPPUNIT_ASSERT(resultVector[0] == 2);
    resultVector = (*pTest).getChildOf(2);
    CPPUNIT_ASSERT(resultVector[0] == 3);


    /* Invalid inputs which should not return any child */
    resultVector = (*pTest).getChildOf(4);
    CPPUNIT_ASSERT(resultVector.empty());
}

// Test whether the getChildOfStar function works as intended.
void ParentTest::testGetChildOfStar() {
    testSet();
    testSetStar();

    /* Valid inputs which should return the correct child* */
    vector<STMTLINE> resultVector = (*pTest).getChildOfStar(1);
    CPPUNIT_ASSERT(resultVector[0] == 2);
    CPPUNIT_ASSERT(resultVector[1] == 8);
    resultVector = (*pTest).getChildOfStar(2);
    CPPUNIT_ASSERT(resultVector[0] == 3);
    resultVector = (*pTest).getChildOfStar(4);
    CPPUNIT_ASSERT(resultVector[0] == 8);
    CPPUNIT_ASSERT(resultVector[1] == 5);

    /* Invalid inputs which should not return any child* */
    resultVector = (*pTest).getChildOfStar(3);
    CPPUNIT_ASSERT(resultVector.empty());
}