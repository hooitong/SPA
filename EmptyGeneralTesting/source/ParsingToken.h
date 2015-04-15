#pragma once

#include <string>
#include "GlobalType.h"

class ParsingToken {
  public:
    ParsingToken(TokenType type, string sValue, int iValue);
    ParsingToken(void);
    ~ParsingToken(void);

    TokenType getTokenType();
    string getStringValue();
    int getIntValue();
    int getDisplayedLineIndex();

    void setTokenType(TokenType type);
    void setStringValue(string sValue);
    void setIntValue(int iValue);
    void setDisplayedLineIndex(int lineIndex);

  private:
    TokenType tokenType;
    string stringValue;
    int intValue;
    int displayedLineIndex;
};