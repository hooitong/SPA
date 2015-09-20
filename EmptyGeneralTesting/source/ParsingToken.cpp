#include "ParsingToken.h"

/* Constructor & Destructor */
ParsingToken::ParsingToken(string sValue, int line) {
  stringValue = sValue;
  lineNumber = line;
}

ParsingToken::ParsingToken(void) {

}

ParsingToken::~ParsingToken(void) {

}

string ParsingToken::getString() {
  return stringValue;
}

int ParsingToken::getLineNumber() {
  return lineNumber;
}