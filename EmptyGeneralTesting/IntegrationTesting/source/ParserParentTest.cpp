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
	CPPUNIT_ASSERT(pTest->isParent(4, 9));
	CPPUNIT_ASSERT(pTest->isParent(4, 22));
    CPPUNIT_ASSERT(pTest->isParent(5, 6));
    CPPUNIT_ASSERT(pTest->isParent(7, 8));
    CPPUNIT_ASSERT(pTest->isParent(9, 10));
    CPPUNIT_ASSERT(pTest->isParent(9, 11));
    CPPUNIT_ASSERT(pTest->isParent(11, 12));
	CPPUNIT_ASSERT(pTest->isParent(11, 13));
	CPPUNIT_ASSERT(pTest->isParent(11, 21));
	CPPUNIT_ASSERT(pTest->isParent(13, 14));
	CPPUNIT_ASSERT(pTest->isParent(13, 15));
	CPPUNIT_ASSERT(pTest->isParent(13, 16));
	CPPUNIT_ASSERT(pTest->isParent(13, 17));
	CPPUNIT_ASSERT(pTest->isParent(13, 20));
	CPPUNIT_ASSERT(pTest->isParent(17, 18));
	CPPUNIT_ASSERT(pTest->isParent(17, 19));
	CPPUNIT_ASSERT(pTest->isParent(23, 24));
	CPPUNIT_ASSERT(pTest->isParent(23, 25));
	CPPUNIT_ASSERT(pTest->isParent(25, 26));
	CPPUNIT_ASSERT(pTest->isParent(25, 27));
	CPPUNIT_ASSERT(pTest->isParent(25, 35));
	CPPUNIT_ASSERT(pTest->isParent(27, 28));
	CPPUNIT_ASSERT(pTest->isParent(27, 29));
	CPPUNIT_ASSERT(pTest->isParent(27, 30));
	CPPUNIT_ASSERT(pTest->isParent(27, 31));
	CPPUNIT_ASSERT(pTest->isParent(27, 34));
	CPPUNIT_ASSERT(pTest->isParent(31, 32));
	CPPUNIT_ASSERT(pTest->isParent(31, 33));
	CPPUNIT_ASSERT(pTest->isParent(36, 37));


	CPPUNIT_ASSERT(!pTest->isParent(1, 2));
	CPPUNIT_ASSERT(!pTest->isParent(4, 8));
	CPPUNIT_ASSERT(!pTest->isParent(13, 18));
	CPPUNIT_ASSERT(!pTest->isParent(23, 26));
	CPPUNIT_ASSERT(!pTest->isParent(25, 28));
	CPPUNIT_ASSERT(!pTest->isParent(27, 32));
}

// Test whether the parser and PKB is able to capture all the Parent* relationship
void ParserParentTest::testParentStar() {
    // from parent relationship above
    CPPUNIT_ASSERT(pTest->isParentStar(4, 5));
	CPPUNIT_ASSERT(pTest->isParentStar(4, 9));
	CPPUNIT_ASSERT(pTest->isParentStar(4, 22));
    CPPUNIT_ASSERT(pTest->isParentStar(5, 6));
    CPPUNIT_ASSERT(pTest->isParentStar(7, 8));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 10));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 11));
    CPPUNIT_ASSERT(pTest->isParentStar(11, 12));
	CPPUNIT_ASSERT(pTest->isParentStar(11, 13));
	CPPUNIT_ASSERT(pTest->isParentStar(11, 21));
	CPPUNIT_ASSERT(pTest->isParentStar(13, 14));
	CPPUNIT_ASSERT(pTest->isParentStar(13, 15));
	CPPUNIT_ASSERT(pTest->isParentStar(13, 16));
	CPPUNIT_ASSERT(pTest->isParentStar(13, 17));
	CPPUNIT_ASSERT(pTest->isParentStar(13, 20));
	CPPUNIT_ASSERT(pTest->isParentStar(17, 18));
	CPPUNIT_ASSERT(pTest->isParentStar(17, 19));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 24));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 25));
	CPPUNIT_ASSERT(pTest->isParentStar(25, 26));
	CPPUNIT_ASSERT(pTest->isParentStar(25, 27));
	CPPUNIT_ASSERT(pTest->isParentStar(25, 35));
	CPPUNIT_ASSERT(pTest->isParentStar(27, 28));
	CPPUNIT_ASSERT(pTest->isParentStar(27, 29));
	CPPUNIT_ASSERT(pTest->isParentStar(27, 30));
	CPPUNIT_ASSERT(pTest->isParentStar(27, 31));
	CPPUNIT_ASSERT(pTest->isParentStar(27, 34));
	CPPUNIT_ASSERT(pTest->isParentStar(31, 32));
	CPPUNIT_ASSERT(pTest->isParentStar(31, 33));
	CPPUNIT_ASSERT(pTest->isParentStar(36, 37));



	CPPUNIT_ASSERT(pTest->isParentStar(4, 6));
	CPPUNIT_ASSERT(pTest->isParentStar(4, 10));
	CPPUNIT_ASSERT(pTest->isParentStar(4, 11));
    CPPUNIT_ASSERT(pTest->isParentStar(4, 12));
	CPPUNIT_ASSERT(pTest->isParentStar(4, 13));
	CPPUNIT_ASSERT(pTest->isParentStar(4, 21));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 11));
    CPPUNIT_ASSERT(pTest->isParentStar(9, 12));
	CPPUNIT_ASSERT(pTest->isParentStar(9, 13));
	CPPUNIT_ASSERT(pTest->isParentStar(9, 21));

	CPPUNIT_ASSERT(pTest->isParentStar(13, 18));
	CPPUNIT_ASSERT(pTest->isParentStar(13, 19));

	CPPUNIT_ASSERT(pTest->isParentStar(23, 26));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 27));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 35));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 28));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 29));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 30));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 31));
	CPPUNIT_ASSERT(pTest->isParentStar(23, 34));

}