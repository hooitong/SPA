#include <cppunit/config/SourcePrefix.h>

#include "ParserSiblingTest.h"

void ParserSiblingTest::setUp() {
	sTest = PKB::getPKB()->getSibling();
}

void ParserSiblingTest::tearDown() {
  sTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserSiblingTest);

// Test whether the parser and PKB is able to capture all the Parent relationship
void ParserSiblingTest::testSibling() {
	CPPUNIT_ASSERT(sTest->isSibling(1, 2));
	CPPUNIT_ASSERT(sTest->isSibling(2, 3));
	CPPUNIT_ASSERT(sTest->isSibling(3, 4));
	CPPUNIT_ASSERT(sTest->isSibling(6, 7));
	CPPUNIT_ASSERT(sTest->isSibling(5, 9));
	CPPUNIT_ASSERT(sTest->isSibling(10, 11));
	CPPUNIT_ASSERT(sTest->isSibling(12, 13));
	CPPUNIT_ASSERT(sTest->isSibling(14, 15));
	CPPUNIT_ASSERT(sTest->isSibling(15, 16));
	CPPUNIT_ASSERT(sTest->isSibling(17, 20));
	CPPUNIT_ASSERT(sTest->isSibling(18, 19));
	CPPUNIT_ASSERT(sTest->isSibling(26, 27));
	CPPUNIT_ASSERT(sTest->isSibling(28, 29));
	CPPUNIT_ASSERT(sTest->isSibling(29, 30));
	CPPUNIT_ASSERT(sTest->isSibling(31, 34));
	CPPUNIT_ASSERT(sTest->isSibling(32, 33));
	CPPUNIT_ASSERT(sTest->isSibling(2, 1));
	CPPUNIT_ASSERT(sTest->isSibling(3, 2));
	CPPUNIT_ASSERT(sTest->isSibling(4, 3));
	CPPUNIT_ASSERT(sTest->isSibling(7, 6));
	CPPUNIT_ASSERT(sTest->isSibling(9, 5));
	CPPUNIT_ASSERT(sTest->isSibling(11, 10));
	CPPUNIT_ASSERT(sTest->isSibling(13, 12));
	CPPUNIT_ASSERT(sTest->isSibling(15, 14));
	CPPUNIT_ASSERT(sTest->isSibling(16, 15));
	CPPUNIT_ASSERT(sTest->isSibling(20, 17));
	CPPUNIT_ASSERT(sTest->isSibling(19, 18));
	CPPUNIT_ASSERT(sTest->isSibling(27, 26));
	CPPUNIT_ASSERT(sTest->isSibling(29, 28));
	CPPUNIT_ASSERT(sTest->isSibling(30, 29));
	CPPUNIT_ASSERT(sTest->isSibling(34, 31));
	CPPUNIT_ASSERT(sTest->isSibling(33, 32));

	//incorrect relationship
	CPPUNIT_ASSERT(!sTest->isSibling(7, 8));
	CPPUNIT_ASSERT(!sTest->isSibling(21, 22));
	CPPUNIT_ASSERT(!sTest->isSibling(17, 18));
	CPPUNIT_ASSERT(!sTest->isSibling(3, 5));
	CPPUNIT_ASSERT(!sTest->isSibling(22, 23));
}


// Test whether the parser and PKB is able to capture all the Parent relationship
void ParserSiblingTest::testGetSiblings() {

	vector<STMTLINE> siblings = sTest->getSiblings(2);
	CPPUNIT_ASSERT(siblings.size() == 2);
	CPPUNIT_ASSERT(siblings[0] == 3);
	CPPUNIT_ASSERT(siblings[1] == 1);
	

	siblings = sTest->getSiblings(11);
	CPPUNIT_ASSERT(siblings.size() == 1);
	CPPUNIT_ASSERT(siblings[0] == 10);
	

	siblings = sTest->getSiblings(37);
	CPPUNIT_ASSERT(siblings.size() == 0);

}
