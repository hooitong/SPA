#pragma once

#include <string>
#include "GlobalType.h"

class ParsingToken 
{
public:
	ParsingToken(TokenType type, string sValue, int iValue);
	~ParsingToken(void);

	TokenType getTokenType();
	string getStringValue();
	int getIntValue();

private:
	TokenType tokenType;
	string stringValue;
	int intValue;
};