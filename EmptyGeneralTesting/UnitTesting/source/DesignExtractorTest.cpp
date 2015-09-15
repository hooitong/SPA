#include <cppunit/config/SourcePrefix.h>

#include "DesignExtractorTest.h"

void DesignExtractorTest::setUp() {
  pkbObj = PKB::getPKB();
}

void DesignExtractorTest::tearDown() {
  pkbObj = nullptr;
}

void DesignExtractorTest::testExtractParentStar() {
  /* Insert sample values on Parent relationship */
  pkbObj->getParent()->setParent(1, 2);
  pkbObj->getParent()->setParent(2, 3);
  pkbObj->getParent()->setParent(3, 4);
  pkbObj->getParent()->setParent(5, 6);

  /* Extract and check for output */
  DesignExtractor::extract();
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(1, 2));
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(1, 3));
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(1, 4));
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(2, 3));
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(2, 4));
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(3, 4));
  CPPUNIT_ASSERT(pkbObj->getParent()->isParentStar(5, 6));

  /* Invalid input check */
  CPPUNIT_ASSERT(!pkbObj->getParent()->isParentStar(1, 5));
  CPPUNIT_ASSERT(!pkbObj->getParent()->isParentStar(1, 6));
}

void DesignExtractorTest::testExtractFollowsStar() {
  /* Insert sample values on Follows relationship */
  pkbObj->getFollows()->setFollows(1, 2);
  pkbObj->getFollows()->setFollows(2, 3);
  pkbObj->getFollows()->setFollows(3, 4);
  pkbObj->getFollows()->setFollows(5, 6);
  pkbObj->getFollows()->setFollows(6, 7);
  pkbObj->getFollows()->setFollows(8, 9);

  /* Extract and check for output */
  DesignExtractor::extract();
  CPPUNIT_ASSERT(pkbObj->getFollows()->isFollowsStar(1, 2));
  CPPUNIT_ASSERT(pkbObj->getFollows()->isFollowsStar(1, 3));
  CPPUNIT_ASSERT(pkbObj->getFollows()->isFollowsStar(1, 4));
  CPPUNIT_ASSERT(pkbObj->getFollows()->isFollowsStar(5, 6));
  CPPUNIT_ASSERT(pkbObj->getFollows()->isFollowsStar(5, 7));

  /* Invalid input check */
  CPPUNIT_ASSERT(!pkbObj->getFollows()->isFollowsStar(1, 5));
  CPPUNIT_ASSERT(!pkbObj->getFollows()->isFollowsStar(6, 8));
  CPPUNIT_ASSERT(!pkbObj->getFollows()->isFollowsStar(6, 9));
}