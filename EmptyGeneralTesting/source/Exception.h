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
};

class InvalidResultSyntaxException: public exception {
};

class InvalidClauseSyntaxException : public exception {
};

class InvalidSelectSyntaxException : public exception {
};

class InvalidCaseClauseException : public exception {
};