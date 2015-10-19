#include <cppunit/config/SourcePrefix.h>

#include "ParserNextTest.h"

void ParserNextTest::setUp() {
  nTest = PKB::getPKB()->getNext();
}

void ParserNextTest::tearDown() {
  nTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserNextTest);

// Test whether the parser and PKB is able to capture all the Next relationship
void ParserNextTest::testNext() {
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
  CPPUNIT_ASSERT(nTest->isNext(21, 9));
  CPPUNIT_ASSERT(nTest->isNext(12, 13));
  CPPUNIT_ASSERT(nTest->isNext(13, 14));
  CPPUNIT_ASSERT(nTest->isNext(13, 17));
  CPPUNIT_ASSERT(nTest->isNext(14, 15));
  CPPUNIT_ASSERT(nTest->isNext(15, 16));
  CPPUNIT_ASSERT(nTest->isNext(17, 18));
  CPPUNIT_ASSERT(nTest->isNext(18, 19));
  CPPUNIT_ASSERT(nTest->isNext(19, 17));
  CPPUNIT_ASSERT(nTest->isNext(17, 20));
  CPPUNIT_ASSERT(nTest->isNext(16, 9));
  CPPUNIT_ASSERT(nTest->isNext(20, 9));
  CPPUNIT_ASSERT(nTest->isNext(23, 24));
  CPPUNIT_ASSERT(nTest->isNext(23, 25));
  CPPUNIT_ASSERT(nTest->isNext(25, 26));
  CPPUNIT_ASSERT(nTest->isNext(25, 35));
  CPPUNIT_ASSERT(nTest->isNext(26, 27));
  CPPUNIT_ASSERT(nTest->isNext(27, 28));
  CPPUNIT_ASSERT(nTest->isNext(28, 29));
  CPPUNIT_ASSERT(nTest->isNext(29, 30));
  CPPUNIT_ASSERT(nTest->isNext(27, 31));
  CPPUNIT_ASSERT(nTest->isNext(31, 32));
  CPPUNIT_ASSERT(nTest->isNext(32, 33));
  CPPUNIT_ASSERT(nTest->isNext(33, 31));
  CPPUNIT_ASSERT(nTest->isNext(31, 34));
  CPPUNIT_ASSERT(nTest->isNext(36, 37));
  CPPUNIT_ASSERT(nTest->isNext(37, 36));

  //incorrect test
  CPPUNIT_ASSERT(!nTest->isNext(5, 10));
  CPPUNIT_ASSERT(!nTest->isNext(8, 5));
  CPPUNIT_ASSERT(!nTest->isNext(4, 23));
  CPPUNIT_ASSERT(!nTest->isNext(7, 9));
  CPPUNIT_ASSERT(!nTest->isNext(9, 22));
  CPPUNIT_ASSERT(!nTest->isNext(16, 17));
  CPPUNIT_ASSERT(!nTest->isNext(30, 31));
  CPPUNIT_ASSERT(!nTest->isNext(33, 34));
  CPPUNIT_ASSERT(!nTest->isNext(35, 36));
}

// Test whether the parser and PKB is able to capture all the Next* relationship
void ParserNextTest::testNextStar() {

  CPPUNIT_ASSERT(nTest->isNextStar(1, 2));
  CPPUNIT_ASSERT(nTest->isNextStar(2, 3));
  CPPUNIT_ASSERT(nTest->isNextStar(3, 4));
  CPPUNIT_ASSERT(nTest->isNextStar(4, 5));
  CPPUNIT_ASSERT(nTest->isNextStar(4, 22));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 6));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(6, 7));
  CPPUNIT_ASSERT(nTest->isNextStar(7, 5));
  CPPUNIT_ASSERT(nTest->isNextStar(7, 8));
  CPPUNIT_ASSERT(nTest->isNextStar(8, 7));
  CPPUNIT_ASSERT(nTest->isNextStar(9, 10));
  CPPUNIT_ASSERT(nTest->isNextStar(10, 11));
  CPPUNIT_ASSERT(nTest->isNextStar(11, 12));
  CPPUNIT_ASSERT(nTest->isNextStar(11, 21));
  CPPUNIT_ASSERT(nTest->isNextStar(21, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(12, 13));
  CPPUNIT_ASSERT(nTest->isNextStar(13, 14));
  CPPUNIT_ASSERT(nTest->isNextStar(13, 17));
  CPPUNIT_ASSERT(nTest->isNextStar(14, 15));
  CPPUNIT_ASSERT(nTest->isNextStar(15, 16));
  CPPUNIT_ASSERT(nTest->isNextStar(17, 18));
  CPPUNIT_ASSERT(nTest->isNextStar(18, 19));
  CPPUNIT_ASSERT(nTest->isNextStar(19, 17));
  CPPUNIT_ASSERT(nTest->isNextStar(17, 20));
  CPPUNIT_ASSERT(nTest->isNextStar(16, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(20, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(21, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(23, 24));
  CPPUNIT_ASSERT(nTest->isNextStar(23, 25));
  CPPUNIT_ASSERT(nTest->isNextStar(25, 26));
  CPPUNIT_ASSERT(nTest->isNextStar(25, 35));
  CPPUNIT_ASSERT(nTest->isNextStar(26, 27));
  CPPUNIT_ASSERT(nTest->isNextStar(27, 28));
  CPPUNIT_ASSERT(nTest->isNextStar(28, 29));
  CPPUNIT_ASSERT(nTest->isNextStar(29, 30));
  CPPUNIT_ASSERT(nTest->isNextStar(27, 31));
  CPPUNIT_ASSERT(nTest->isNextStar(31, 32));
  CPPUNIT_ASSERT(nTest->isNextStar(32, 33));
  CPPUNIT_ASSERT(nTest->isNextStar(33, 31));
  CPPUNIT_ASSERT(nTest->isNextStar(31, 34));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 37));
  CPPUNIT_ASSERT(nTest->isNextStar(37, 36));

  CPPUNIT_ASSERT(nTest->isNextStar(1, 3));
  CPPUNIT_ASSERT(nTest->isNextStar(1, 8));
  CPPUNIT_ASSERT(nTest->isNextStar(1, 16));
  CPPUNIT_ASSERT(nTest->isNextStar(1, 20));
  CPPUNIT_ASSERT(nTest->isNextStar(1, 22));
  CPPUNIT_ASSERT(!nTest->isNextStar(1, 23));

  CPPUNIT_ASSERT(nTest->isNextStar(5, 5));
  CPPUNIT_ASSERT(nTest->isNextStar(5, 8));
  CPPUNIT_ASSERT(nTest->isNextStar(8, 5));
  CPPUNIT_ASSERT(nTest->isNextStar(8, 8));

  CPPUNIT_ASSERT(nTest->isNextStar(9, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(9, 16));
  CPPUNIT_ASSERT(nTest->isNextStar(9, 19));
  CPPUNIT_ASSERT(nTest->isNextStar(19, 9));
  CPPUNIT_ASSERT(nTest->isNextStar(17, 19));
  CPPUNIT_ASSERT(nTest->isNextStar(20, 17));
  CPPUNIT_ASSERT(nTest->isNextStar(20, 21));
  CPPUNIT_ASSERT(!nTest->isNextStar(20, 22));

  CPPUNIT_ASSERT(!nTest->isNextStar(22, 23));
  CPPUNIT_ASSERT(!nTest->isNextStar(22, 36));

  CPPUNIT_ASSERT(nTest->isNextStar(23, 33));
  CPPUNIT_ASSERT(!nTest->isNextStar(24, 33));

  CPPUNIT_ASSERT(nTest->isNextStar(36, 36));
  CPPUNIT_ASSERT(nTest->isNextStar(36, 37));
  CPPUNIT_ASSERT(nTest->isNextStar(37, 36));
}