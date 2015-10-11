#include <cppunit/config/SourcePrefix.h>
#include <algorithm>

#include "ParserConstTableTest.h"

void ParserConstTableTest::setUp() {
	cTest = PKB::getPKB()->getConstTable();
}

void ParserConstTableTest::tearDown() {
	cTest = nullptr;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserConstTableTest);

void ParserConstTableTest::testConstTableItems() {
	vector<CONSTVALUE> vec = cTest->getAllConstValue();
	CPPUNIT_ASSERT(vec.size()==14);
	CPPUNIT_ASSERT(containConstant(&vec, 1));
	CPPUNIT_ASSERT(containConstant(&vec, 0));
	CPPUNIT_ASSERT(containConstant(&vec, 200));

	CPPUNIT_ASSERT(!containConstant(&vec, 2));
}

bool ParserConstTableTest::containConstant(vector<CONSTVALUE> *list, CONSTVALUE v){
	return find(list->begin(), list->end(), v) != list->end();
}
