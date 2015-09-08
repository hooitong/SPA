#include <cppunit/config/SourcePrefix.h>
#include <fstream>

#include "TokenizerTest.h"
#include "Tokenizer.h"

void TokenizerTest::setUp() {
}

void TokenizerTest::tearDown() {

}

CPPUNIT_TEST_SUITE_REGISTRATION(TokenizerTest);

void TokenizerTest::testTokenize() {
	Tokenizer tokenizer = Tokenizer::Tokenizer();
	vector<ParsingToken> tokens;
	tokenizer.tokenizeLine("x=y+1 (-2) * 1 \\\\abchd ", 5, tokens);

	CPPUNIT_ASSERT(tokens.size() == 11);
	CPPUNIT_ASSERT(tokens.at(0).getString() == "x");
	CPPUNIT_ASSERT(tokens.at(3).getString() == "+");
}