#include "Exception.h"

InvalidNameException::InvalidNameException(STMTLINE line) {
    lineIndex = line;
}

InvalidNameException::~InvalidNameException() {

}

string InvalidNameException::message() {
    string message = "Duplicate procedure name error.";
    return message;
}

InvalidProcedureException::InvalidProcedureException(STMTLINE line) {
	lineIndex = line;
}

InvalidProcedureException::~InvalidProcedureException() {

}

string InvalidProcedureException::message() {
    string s = std::to_string(static_cast<long long>(lineIndex));
    string message = "Invalid procedure call at line ";
    return message.append(s);
}

SyntaxErrorException::SyntaxErrorException(STMTLINE line) {
    lineIndex = line;
}

SyntaxErrorException::~SyntaxErrorException() {

}

string SyntaxErrorException::message() {
    string s = std::to_string(static_cast<long long>(lineIndex));
    string message = "Syntax error at line ";
    return message.append(s);
}

RecursiveCallException::RecursiveCallException(STMTLINE line) {
    lineIndex = line;
}

RecursiveCallException::~RecursiveCallException() {

}

string RecursiveCallException::message() {
    string s = std::to_string(static_cast<long long>(lineIndex));
    string message = "Recursive call error at line ";
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

UndeclaredException::UndeclaredException() {

}

UndeclaredException::~UndeclaredException() {

}

string UndeclaredException::message() {
    return "Undeclared synonym declaration ";
}

UnmatchedSynonymException::UnmatchedSynonymException() {

}

UnmatchedSynonymException::~UnmatchedSynonymException() {

}

string UnmatchedSynonymException::message() {
    return "Synonym type mismatched";
}
