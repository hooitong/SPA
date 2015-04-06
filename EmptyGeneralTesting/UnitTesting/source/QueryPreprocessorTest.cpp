#include <cppunit/config/SourcePrefix.h>

#include "QueryPreprocessorTest.h"
#include "QueryPreprocessor.h"
#include <string>

 void QueryPreprocessorTest::setUp(){
     QueryPreprocessor* queryTest = new QueryPreprocessor();
}

void QueryPreprocessorTest::tearDown(){
    delete queryTest;

}
CPPUNIT_TEST_SUITE_REGISTRATION(QueryPreprocessorTest);
void QueryPreprocessorTest::testParsing(){

	QueryTree* queryTree = (*queryTest).parseQuery("assign a; Select BOOLEAN such that Modifies(a, _)");
	//CPPUNIT_ASSERT(queryTree->getRoot()->getQType() == QUERY);
	//CPPUNIT_ASSERT(queryTree->getRoot()->getString() == "query");


}
