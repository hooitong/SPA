#include <cppunit/config/SourcePrefix.h>

#include "GrammarTest.h"

void GrammarTest::setUp() {

}

void GrammarTest::tearDown() {

}

CPPUNIT_TEST_SUITE_REGISTRATION(GrammarTest);

void GrammarTest::testSetup() {
    
	Grammar* grammer = new Grammar();

}

void GrammarTest::testConvert() {
    
	Grammar* grammer = new Grammar();
	map<GrammarTType, string> typeToStringMap;
	typeToStringMap.insert(make_pair<GrammarTType, string>(G_PROGRAM, "PROCEDURE+"));
	typeToStringMap.insert(make_pair<GrammarTType, string>(G_FACTOR, "VAR_NAME | CONST_VALUE | '(' EXPR ')'"));
	typeToStringMap.insert(make_pair<GrammarTType, string>(G_PROC_NAME, "NAME"));
	typeToStringMap.insert(make_pair<GrammarTType, string>(G_CONST_VALUE, "INTEGER"));


	map<GrammarTType, GrammarToken> result = grammer->convertStringMapToTokenMap(typeToStringMap);
	GrammarToken programT = result.find(G_PROGRAM)->second; 
	CPPUNIT_ASSERT(programT.getType() == G_PROGRAM);
	CPPUNIT_ASSERT(programT.isAllowMultiple() == false);
	CPPUNIT_ASSERT(programT.getExpectedTokensList().at(0).at(0).isAllowMultiple() == true);
	CPPUNIT_ASSERT(programT.getExpectedTokensList().at(0).at(0).getType() == G_PROCEDURE);
	
	GrammarToken factorT = result.find(G_FACTOR)->second;
	CPPUNIT_ASSERT(factorT.getType() == G_FACTOR);
	CPPUNIT_ASSERT(factorT.isAllowMultiple() == false);
	CPPUNIT_ASSERT(factorT.getExpectedTokensList().at(2).at(2).getType() == G_TEXT);
	CPPUNIT_ASSERT(factorT.getExpectedTokensList().at(2).at(2).getString() == ")");
	
	GrammarToken constantT = result.find(G_CONST_VALUE)->second;
	CPPUNIT_ASSERT(constantT.getType() == G_CONST_VALUE);
	CPPUNIT_ASSERT(constantT.getExpectedTokensList().at(0).at(0).getType() == G_INTEGER);
	
}