#include "NextTest.h"

void NextTest::setUp() {
  next = new Next;
}

void NextTest::tearDown() {
  delete next;
}

CPPUNIT_TEST_SUITE_REGISTRATION(NextTest);

// Test whether setNext function works as intended
void NextTest::testSetNext() {
  (*next).setNext(1, 2);
  (*next).setNext(2, 3);
  (*next).setNext(3, 4);
  (*next).setNext(3, 5);
  (*next).setNext(5, 3);
}


// Test whether isNext function works as intended
void NextTest::testIsNext() {
  testSetNext();

  /* Valid input and true is returned */
  CPPUNIT_ASSERT((*next).isNext(1, 2));
  CPPUNIT_ASSERT((*next).isNext(2, 3));
  CPPUNIT_ASSERT((*next).isNext(3, 4));
  CPPUNIT_ASSERT((*next).isNext(3, 5));
  CPPUNIT_ASSERT((*next).isNext(5, 3));

  /* Invalid input and false is returned */
  CPPUNIT_ASSERT(!(*next).isNext(1, 3));
  CPPUNIT_ASSERT(!(*next).isNext(1, 4));
  CPPUNIT_ASSERT(!(*next).isNext(5, 1));
  CPPUNIT_ASSERT(!(*next).isNext(4, 3));
  CPPUNIT_ASSERT(!(*next).isNext(1, 6));
  CPPUNIT_ASSERT(!(*next).isNext(0, 0));
}

// Test whether isNextStar function works as intended
void NextTest::testIsNextStar() {
  testSetNext();

  /* Valid input and true is returned */
  CPPUNIT_ASSERT((*next).isNextStar(1, 2));
  CPPUNIT_ASSERT((*next).isNextStar(1, 3));
  CPPUNIT_ASSERT((*next).isNextStar(1, 4));
  CPPUNIT_ASSERT((*next).isNextStar(1, 5));
  CPPUNIT_ASSERT((*next).isNextStar(2, 3));
  CPPUNIT_ASSERT((*next).isNextStar(2, 4));
  CPPUNIT_ASSERT((*next).isNextStar(2, 5));
  CPPUNIT_ASSERT((*next).isNextStar(3, 4));
  CPPUNIT_ASSERT((*next).isNextStar(3, 5));
  CPPUNIT_ASSERT((*next).isNextStar(5, 5));

  /* Invalid input and false is returned */
  CPPUNIT_ASSERT(!(*next).isNextStar(4, 1));
  CPPUNIT_ASSERT(!(*next).isNextStar(5, 1));
  CPPUNIT_ASSERT(!(*next).isNextStar(3, 2));
  CPPUNIT_ASSERT(!(*next).isNextStar(4, 2));
  CPPUNIT_ASSERT(!(*next).isNextStar(1, 1));
  CPPUNIT_ASSERT(!(*next).isNextStar(2, 2));
}

// Test whether getBefore function works as intended
void NextTest::testGetBefore() {
  testSetNext();

  vector<PROGLINE> v = (*next).getBefore(2);
  CPPUNIT_ASSERT(v[0] == 1);
  CPPUNIT_ASSERT(v.size() == 1);

  v = (*next).getBefore(4);
  CPPUNIT_ASSERT(v[0] == 3);
  CPPUNIT_ASSERT(v.size() == 1);
}

// Test whether getBeforeStar function works as intended
void NextTest::testGetBeforeStar() {
  testSetNext();


  vector<PROGLINE> v = (*next).getBeforeStar(4);
  CPPUNIT_ASSERT(v[0] == 3);
  CPPUNIT_ASSERT(v[1] == 2);
  CPPUNIT_ASSERT(v[2] == 1);
  CPPUNIT_ASSERT(v[3] == 5);
  CPPUNIT_ASSERT(v.size() == 4);
}


// Test whether getNext function works as intended
void NextTest::testGetNext() {
  testSetNext();

  vector<PROGLINE> v = (*next).getNext(2);
  CPPUNIT_ASSERT(v[0] == 3);
  CPPUNIT_ASSERT(v.size() == 1);
}


// Test whether getNextStar function works as intended
void NextTest::testGetNextStar() {
  testSetNext();

  vector<PROGLINE> v = (*next).getNextStar(1);
  CPPUNIT_ASSERT(v[0] == 2);
  CPPUNIT_ASSERT(v[1] == 3);
  CPPUNIT_ASSERT(v[2] == 4);
  CPPUNIT_ASSERT(v[3] == 5);
  CPPUNIT_ASSERT(v.size() == 4);
}