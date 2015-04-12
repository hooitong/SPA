#include "InvalidNameException.h"

InvalidNameException::InvalidNameException(STMTLINE line) {
	lineIndex = line;
}

InvalidNameException::~InvalidNameException() {

}

string InvalidNameException::message() {
	string s = std::to_string(static_cast<long long>(lineIndex));
	string message = "Invalid name error at line ";
	return message.append(s);
}