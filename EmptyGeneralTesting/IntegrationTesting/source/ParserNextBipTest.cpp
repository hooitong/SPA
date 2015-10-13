#include <cppunit/config/SourcePrefix.h>

#include "ParserNextBipTest.h"

void ParserNextBipTest::setUp() {
  nTest = PKB::getPKB()->getNextBip();
}

void ParserNextBipTest::tearDown() {
  nTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserNextBipTest);

// Test whether the parser and PKB is able to capture all the NextBip relationship
void ParserNextBipTest::testNext() {
  // Correct Relationships
  CPPUNIT_ASSERT(nTest->isNext(1, 2));
  CPPUNIT_ASSERT(nTest->isNext(2, 3));
  CPPUNIT_ASSERT(nTest->isNext(3, 4));
  CPPUNIT_ASSERT(nTest->isNext(4, 5));
  CPPUNIT_ASSERT(nTest->isNext(4, 22));
  CPPUNIT_ASSERT(nTest->isNext(5, 6));
  CPPUNIT_ASSERT(nTest->isNext(5, 9));
  CPPUNIT_ASSERT(nTest->isNext(6, 7));
  CPPUNIT_ASSERT(nTest->isNext(7, 5));
  CPPUNIT_ASSERT(nTest->isNext(7, 8));
  CPPUNIT_ASSERT(nTest->isNext(8, 7));
  CPPUNIT_ASSERT(nTest->isNext(9, 10));
  CPPUNIT_ASSERT(nTest->isNext(10, 11));
  CPPUNIT_ASSERT(nTest->isNext(11, 12));
  CPPUNIT_ASSERT(nTest->isNext(11, 21));
  CPPUNIT_ASSERT(nTest->isNext(21, 36));
  CPPUNIT_ASSERT(nTest->isNext(12, 23));
  CPPUNIT_ASSERT(nTest->isNext(13, 14));
  CPPUNIT_ASSERT(nTest->isNext(13, 17));
  CPPUNIT_ASSERT(nTest->isNext(14, 15));
  CPPUNIT_ASSERT(nTest->isNext(15, 16));
  CPPUNIT_ASSERT(nTest->isNext(17, 18));
  CPPUNIT_ASSERT(nTest->isNext(18, 36));
  CPPUNIT_ASSERT(nTest->isNext(19, 17));
  CPPUNIT_ASSERT(nTest->isNext(17, 20));
  CPPUNIT_ASSERT(nTest->isNext(16, 9));
  CPPUNIT_ASSERT(nTest->isNext(20, 9));
  CPPUNIT_ASSERT(nTest->isNext(22, 36));
  CPPUNIT_ASSERT(nTest->isNext(23, 24));
  CPPUNIT_ASSERT(nTest->isNext(23, 25));
  CPPUNIT_ASSERT(nTest->isNext(24, 13));
  CPPUNIT_ASSERT(nTest->isNext(25, 26));
  CPPUNIT_ASSERT(nTest->isNext(25, 35));
  CPPUNIT_ASSERT(nTest->isNext(26, 36));
  CPPUNIT_ASSERT(nTest->isNext(27, 28));
  CPPUNIT_ASSERT(nTest->isNext(28, 29));
  CPPUNIT_ASSERT(nTest->isNext(29, 30));
  CPPUNIT_ASSERT(nTest->isNext(30, 13));
  CPPUNIT_ASSERT(nTest->isNext(27, 31));
  CPPUNIT_ASSERT(nTest->isNext(31, 32));
  CPPUNIT_ASSERT(nTest->isNext(32, 36));
  CPPUNIT_ASSERT(nTest->isNext(33, 31));
  CPPUNIT_ASSERT(nTest->isNext(34, 13));
  CPPUNIT_ASSERT(nTest->isNext(31, 34));
  CPPUNIT_ASSERT(nTest->isNext(35, 36));
  CPPUNIT_ASSERT(nTest->isNext(36, 37));
  CPPUNIT_ASSERT(nTest->isNext(36, 19));
  CPPUNIT_ASSERT(nTest->isNext(36, 33));
  CPPUNIT_ASSERT(nTest->isNext(36, 27));
  CPPUNIT_ASSERT(nTest->isNext(37, 36));

  //incorrect test
  CPPUNIT_ASSERT(!nTest->isNext(5, 10));
  CPPUNIT_ASSERT(!nTest->isNext(8, 5));
  CPPUNIT_ASSERT(!nTest->isNext(4, 23));
  CPPUNIT_ASSERT(!nTest->isNext(7, 9));
  CPPUNIT_ASSERT(!nTest->isNext(9, 22));
  CPPUNIT_ASSERT(!nTest->isNext(12, 13));
  CPPUNIT_ASSERT(!nTest->isNext(16, 17));
  CPPUNIT_ASSERT(!nTest->isNext(18, 19));
  CPPUNIT_ASSERT(!nTest->isNext(21, 9));
  CPPUNIT_ASSERT(!nTest->isNext(26, 27));
  CPPUNIT_ASSERT(!nTest->isNext(30, 31));
  CPPUNIT_ASSERT(!nTest->isNext(32, 33));
  CPPUNIT_ASSERT(!nTest->isNext(33, 34));
}

// Test whether the parser and PKB is able to capture all the Next* relationship
void ParserNextBipTest::testNextStar() {

  // Correct Relationships
  CPPUNIT_ASSERT(nTest->isNextStar(1, 2));
  CPPUNIT_ASSERT(nTest->isNextStar(2, 3));
  CPPUNIT_ASSERT(nTest->isNextStar(3, 4));
  CPPUNIT_ASSERT(nTest->isNextStar(3, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(4, 5));
  CPPUNIT_ASSERT(nTest->isNextStar(4, 22));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 6));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 30));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(6, 7));
  CPPUNIT_ASSERT(nTest->isNextStar(7, 5));
  CPPUNIT_ASSERT(nTest->isNextStar(7, 8));
  CPPUNIT_ASSERT(nTest->isNextStar(8, 7));
  CPPUNIT_ASSERT(nTest->isNextStar(9, 10));
  CPPUNIT_ASSERT(nTest->isNextStar(10, 11));
  CPPUNIT_ASSERT(nTest->isNextStar(11, 12));
  CPPUNIT_ASSERT(nTest->isNextStar(11, 21));
  CPPUNIT_ASSERT(nTest->isNextStar(21, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(12, 23));
  CPPUNIT_ASSERT(nTest->isNextStar(12, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(13, 14));
  CPPUNIT_ASSERT(nTest->isNextStar(13, 17));
  CPPUNIT_ASSERT(nTest->isNextStar(14, 15));
  CPPUNIT_ASSERT(nTest->isNextStar(15, 16));
  CPPUNIT_ASSERT(nTest->isNextStar(17, 18));
  CPPUNIT_ASSERT(nTest->isNextStar(18, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(19, 17));
  CPPUNIT_ASSERT(nTest->isNextStar(19, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(17, 20));
  CPPUNIT_ASSERT(nTest->isNextStar(16, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(20, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(22, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(23, 24));
  CPPUNIT_ASSERT(nTest->isNextStar(23, 25));
  CPPUNIT_ASSERT(nTest->isNextStar(24, 13));
  CPPUNIT_ASSERT(nTest->isNextStar(25, 26));
  CPPUNIT_ASSERT(nTest->isNextStar(25, 35));
  CPPUNIT_ASSERT(nTest->isNextStar(26, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(27, 28));
  CPPUNIT_ASSERT(nTest->isNextStar(28, 29));
  CPPUNIT_ASSERT(nTest->isNextStar(28, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(29, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(30, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(29, 30));
  CPPUNIT_ASSERT(nTest->isNextStar(30, 13));
  CPPUNIT_ASSERT(nTest->isNextStar(27, 31));
  CPPUNIT_ASSERT(nTest->isNextStar(31, 32));
  CPPUNIT_ASSERT(nTest->isNextStar(32, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(33, 31));
  CPPUNIT_ASSERT(nTest->isNextStar(34, 13));
  CPPUNIT_ASSERT(nTest->isNextStar(31, 34));
  CPPUNIT_ASSERT(nTest->isNextStar(33, 15));
  CPPUNIT_ASSERT(nTest->isNextStar(35, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 11));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 13));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 15));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 17));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 20));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 21));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 23));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 37));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 19));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 33));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 27));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 24));
  CPPUNIT_ASSERT(nTest->isNextStar(37, 36));

  //incorrect test
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 1));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 2));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 3));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 4));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 5));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 6));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 7));
  CPPUNIT_ASSERT(!nTest->isNextStar(36, 8));
  
}