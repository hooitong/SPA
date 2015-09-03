#pragma once

#include <string>
#include "GlobalType.h"

class ParsingToken {
  public:
    ParsingToken(string s, int line);
    ParsingToken(void);
    ~ParsingToken(void);

	string getString();
	int getLineNumber();
   
  private:
    string stringValue;
    int lineNumber;
};