#pragma once
#include<string>

using namespace std;
typedef string PROCNAME, VARNAME;
typedef int PROCINDEX, PROGLINE, STMTLINE, VARINDEX, CONSTINDEX;

//Used to represent the type of the TNode
enum TType {
    PROCEDUREN,
    STMTLSTN,
    ASSIGNN,
    WHILEN,
    VARN,
    CONSTN,
    PLUSN,
    MINUSN,
    TIMESN
};

// Used to represent the type of the QNode
enum QNodeType {
    QUERY,
    SUCHTHATLIST,
    WITHLIST,
    PATTERNLIST,
    RESULTLIST,
    STMTSYNONYM,
    ASSIGNSYNONYM,
    WHILESYNONYM,
    VARIABLESYNONYM,
    CONSTSYNONYM,
    PROGLINESYNONYM,
    PROCEDURESYNONYM,
    IFSYNONYM,
    PATTERN,
    RELATION,
    EXPRESSION,
    BOOLEAN,
    ASSIGN,
    WHILE,
    VAR,
    CONST,
    PROC,
    IF
};

// Used to represent the type of ParsingToken
enum TokenType {
	PROCEDURE_TOKEN, // procedure
	WHILE_TOKEN, // while
	IF_TOKEN, // if
	ELSE_TOKEN, // else
	ID, // identifier
	CONSTANT, // 1
	ASSIGNMENT_TOKEN, // =
	PLUS, // +
	MINUS, // -
	SEMICOLON,  // ;
	OPEN_CURLY_BRACKET, // {
	CLOSE_CURLY_BRACKET // }
};