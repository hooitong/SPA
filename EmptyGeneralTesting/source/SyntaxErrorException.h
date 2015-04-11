#pragma once

#include <exception>
#include <iostream>
#include "GlobalType.h"

using namespace std;

class SyntaxErrorException : public exception {
public:
	SyntaxErrorException(STMTLINE line);
	~SyntaxErrorException();

	string message();

private:
	STMTLINE lineIndex;
};