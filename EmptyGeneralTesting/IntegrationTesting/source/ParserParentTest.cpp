#include <cppunit/config/SourcePrefix.h>

#include "ParserParentTest.h"

void ParserParentTest::setUp() {
    pTest = PKB::getPKB()->getParent();
}

void ParserParentTest::tearDown() {
    pTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserParentTest);

// Test whether the parser and PKB is able to capture all the Parent relationship
void ParserParentTest::testParent() {
    CPPUNIT_ASSERT(pTest->isParent(4, 5));
    CPPUNIT_ASSERT(pTest->isParent(4, 20));
    CPPUNIT_ASSERT(pTest->isParent(5, 6));
    CPPUNIT_ASSERT(pTest->isParent(5, 7));
    CPPUNIT_ASSERT(pTest->isParent(5, 9));
    CPPUNIT_ASSERT(pTest->isParent(5, 19));
    CPPUNIT_ASSERT(pTest->isParent(7, 8));
    CPPUNIT_ASSERT(pTest->isParent(9, 10));
    CPPUNIT_ASSERT(pTest->isParent(9, 11));
    CPPUNIT_ASSERT(pTest->isParent(11, 12));
    CPPUNIT_ASSERT(pTest->isParent(11, 16));
    CPPUNIT_ASSERT(pTest->isParent(11, 18));
    CPPUNIT_ASSERT(pTest->isParent(12, 13));
    CPPUNIT_ASSERT(pTest->isParent(12, 14));
    CPPUNIT_ASSERT(pTest->isParent(12, 15));
    CPPUNIT_ASSERT(pTest->isParent(16, 17));
}

// Test whether the parser and PKB is able to capture all the Parent* relationship
void ParserParentTest::testParentStar() {
    // from parent relationship above
    CPPUNIT_ASSERT(pTest->isParentStar(4, 5));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 20));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 6));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 7));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 9));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 19));
    CPPUNIT_ASSERT(pTest->isParentStar(7, 8));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 10));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 11));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 12));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 16));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 18));
    CPPUNIT_ASSERT(pTest->isParentStar(12, 13));
    CPPUNIT_ASSERT(pTest->isParentStar(12, 14));
    CPPUNIT_ASSERT(pTest->isParentStar(12, 15));
    CPPUNIT_ASSERT(pTest->isParentStar(16, 17));

    // except the above
    CPPUNIT_ASSERT(pTest->isParentStar(4, 6));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 7));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 9));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 19));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 8));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 10));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 11));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 12));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 16));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 18));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 13));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 14));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 15));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 17));

    CPPUNIT_ASSERT(pTest->isParentStar(5, 8));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 11));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 13));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 14));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 15));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 17));

    CPPUNIT_ASSERT(pTest->isParentStar(9, 13));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 14));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 15));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 17));

    CPPUNIT_ASSERT(pTest->isParentStar(11, 13));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 14));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 15));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 17));

}