#pragma once

#include <exception>
#include <iostream>
#include "GlobalType.h"

using namespace std;

class InvalidNameException : public exception {
public:
	InvalidNameException(STMTLINE line);
	~InvalidNameException();

	string message();

private:
	STMTLINE lineIndex;
};