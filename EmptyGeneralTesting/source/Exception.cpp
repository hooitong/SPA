#include "Exception.h"

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

InvalidSelectException::InvalidSelectException() {

}

InvalidSelectException::~InvalidSelectException() {

}

string InvalidSelectException::message() {
	return "Select not found ";
}

InvalidCaseClauseException::InvalidCaseClauseException() {

}

InvalidCaseClauseException::~InvalidCaseClauseException() {

}

string InvalidCaseClauseException::message() {
	return " clause should be lower case";
}

InvalidClauseSyntaxException::InvalidClauseSyntaxException() {

}

InvalidClauseSyntaxException::~InvalidClauseSyntaxException() {

}

string InvalidClauseSyntaxException::message() {
	return "Invalid Clause Syntax ";
}

InvalidResultSyntaxException::InvalidResultSyntaxException() {

}

InvalidResultSyntaxException::~InvalidResultSyntaxException() {

}

string InvalidResultSyntaxException::message() {
	return "Invalid Result Syntax ";
}

InvalidQueryDeclarationException::InvalidQueryDeclarationException() {

}

InvalidQueryDeclarationException::~InvalidQueryDeclarationException() {

}

string InvalidQueryDeclarationException::message() {
	return "Invalid Query Declaration ";
}
