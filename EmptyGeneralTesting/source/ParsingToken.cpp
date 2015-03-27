#include "ParsingToken.h"

/* Constructor & Destructor */
ParsingToken::ParsingToken(TokenType type, string sValue, int iValue) {
	tokenType = type;
	stringValue = sValue;
	intValue = iValue;
}

ParsingToken::~ParsingToken(void) {

}

TokenType ParsingToken::getTokenType() {
	return tokenType;
}

string ParsingToken::getStringValue() {
	return stringValue;
}

int ParsingToken::getIntValue() {
	return intValue;
}