#pragma once
#include <map>
#include <vector>
#include <string>
#include <exception>
#include "GlobalType.h"
#include "ParsingToken.h"

class Parser {

public:
	Parser(void);
    ~Parser(void);
    static vector<string> tokenizeLine(string line);
	static ParsingToken convertStringToToken(string aString);
	static bool isNumeric(string aString);
	static bool isValidName(string aString);
};