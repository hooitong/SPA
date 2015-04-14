#include "Exceptions.h"

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

InvalidProcedureException::InvalidProcedureException() {

}

InvalidProcedureException::~InvalidProcedureException() {

}

string InvalidProcedureException::message() {
	return "Invalid procedure ";
}

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


InvalidSelectSyntaxException::InvalidSelectSyntaxException() {

}

InvalidSelectSyntaxException::~InvalidSelectSyntaxException() {

}

string InvalidSelectSyntaxException::message() {
	return "Select not found ";
}