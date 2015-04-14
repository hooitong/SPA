#pragma once

#include <exception>
#include <iostream>
#include "GlobalType.h"

class InvalidNameException : public exception {
  public:
    InvalidNameException(STMTLINE line);
    ~InvalidNameException();

    string message();

  private:
    STMTLINE lineIndex;
};

class InvalidProcedureException : public exception {
  public:
    InvalidProcedureException();
    ~InvalidProcedureException();

    string message();
};

class SyntaxErrorException : public exception {
  public:
    SyntaxErrorException(STMTLINE line);
    ~SyntaxErrorException();

    string message();

  private:
    STMTLINE lineIndex;
};

class InvalidQueryDeclarationException : public exception {
	public:
    InvalidQueryDeclarationException ();
    ~InvalidQueryDeclarationException ();

    string message();
};

class InvalidResultSyntaxException: public exception {
	public:
    InvalidResultSyntaxException();
    ~InvalidResultSyntaxException();

    string message();
};

class InvalidClauseSyntaxException : public exception {
	public:
    InvalidClauseSyntaxException();
    ~InvalidClauseSyntaxException();

    string message();
};

class InvalidSelectException : public exception {

	public:
    InvalidSelectException();
    ~InvalidSelectException();

    string message();
};

class InvalidCaseClauseException : public exception {
	public:
    InvalidCaseClauseException();
    ~InvalidCaseClauseException();

    string message();
};

class UndeclaredException : public exception {
	public:
    UndeclaredException();
    ~UndeclaredException();

    string message();
};

class UnmatchedSynonymException : public exception {
	public:
    UnmatchedSynonymException();
    ~UnmatchedSynonymException();

    string message();
};