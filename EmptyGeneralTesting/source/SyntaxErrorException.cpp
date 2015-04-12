#include "SyntaxErrorException.h"

SyntaxErrorException::SyntaxErrorException(STMTLINE line) {
	lineIndex = line;
}

SyntaxErrorException::~SyntaxErrorException() {

}

string SyntaxErrorException::message() {
	string s = std::to_string(static_cast<long long>(lineIndex));
	string message = "Invalid name error at line ";
	return message.append(s);
}