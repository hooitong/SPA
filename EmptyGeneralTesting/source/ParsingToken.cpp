#include "ParsingToken.h"

/* Constructor & Destructor */
ParsingToken::ParsingToken(TokenType type, string sValue, int iValue) {
    tokenType = type;
    stringValue = sValue;
    intValue = iValue;
}

ParsingToken::ParsingToken(void) {

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

int ParsingToken::getDisplayedLineIndex() {
    return displayedLineIndex;
}

void ParsingToken::setTokenType(TokenType type) {
    tokenType = type;
}

void ParsingToken::setStringValue(string sValue) {
    stringValue = sValue;
}

void ParsingToken::setIntValue(int iValue) {
    intValue = iValue;
}

void ParsingToken::setDisplayedLineIndex(int lineIndex) {
    displayedLineIndex = lineIndex;
}