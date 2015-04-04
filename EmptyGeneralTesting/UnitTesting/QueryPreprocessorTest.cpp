#include <cppunit/config/SourcePrefix.h>

#include "QueryPreprocessorTest.h"
#include "QueryPreprocessor.h"

void QueryPreprocessorTest::setUp() {
     QueryPreprocessor* queryTest = new QueryPreprocessor;
}

void QueryPreprocessorTest::tearDown() {
    delete queryTest;

}

void QueryPreprocessorTest::testParsing(){

	(*queryTest).parseQuery("assign a; Select BOOLEAN such that Modifies(a, _)");


}
