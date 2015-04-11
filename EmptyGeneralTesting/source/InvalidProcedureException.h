#pragma once

#include <exception>
#include <iostream>
#include "GlobalType.h"

using namespace std;

class InvalidProcedureException : public exception {
public:
	InvalidProcedureException();
	~InvalidProcedureException();

	string message();
};