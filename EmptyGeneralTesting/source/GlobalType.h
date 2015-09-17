#pragma once

#include<string>

using namespace std;
typedef string PROCNAME, VARNAME;
typedef int PROCINDEX, PROGLINE, STMTLINE, VARINDEX, CONSTINDEX;

//Used to represent the type of the TNode
enum TType {
	PROGRAMN,
    PROCEDUREN,
    STMTLSTN,
	CALLN,
	IFN,
    ASSIGNN,
    WHILEN,
    STMTN,
    VARN,
    CONSTN,
    PLUSN,
    MINUSN,
    TIMESN,
	UNKNOWNN,
	EMPTYN
};

// Used to represent the type of the QNode
enum QNodeType {
    QUERY,
    SUCHTHATLIST,
    WITHLIST,
    PATTERNLIST,
	CONDITIONLIST,
    RESULTLIST,
    STMTSYNONYM,
	STMTLSTSYNONYM,
    ASSIGNSYNONYM,
    WHILESYNONYM,
    VARIABLESYNONYM,
    CONSTSYNONYM,
    PROGLINESYNONYM,
    PROCEDURESYNONYM,
	CALLSYNONYM,
    IFSYNONYM,
    PATTERN,
    RELATION,
	ATTRIBUTE,
	INTERGER,
    EXPRESSION,
    BOOLEAN,
    ASSIGN,
    WHILE,
    VAR,
    CONST,
    PROC,
    IF,
    ANY
};

// Used to represent the type of ParsingToken
enum TokenType {
    PROCEDURE_TOKEN, // procedure
    WHILE_TOKEN, // while
    IF_TOKEN, // if
    ELSE_TOKEN, // else
    NAME, // name
    CONSTANT, // 1
    ASSIGNMENT_TOKEN, // =
    PLUS, // +
    MINUS, // -
    SEMICOLON,  // ;
    OPEN_CURLY_BRACKET, // {
    CLOSE_CURLY_BRACKET // }
};

// Used to represent the type of GrammarToken, according to handbook page 11
enum GrammarTType {
    G_PROGRAM, 
    G_PROCEDURE, 
    G_STMTLST, 
    G_STMT, 
	G_ELSE_STMTLST,
    G_CALL, 
    G_WHILE, 
    G_IF, 
    G_ASSIGN, 
    G_EXPR,
    G_TERM, 
    G_FACTOR,
    G_VAR_NAME,
	G_PROC_NAME,
	G_CONST_VALUE,
	G_NAME,
	G_INTEGER,
	G_EMPTY,
	G_TEXT
};

// Used to represent the relationship between tree node
enum TNodeRelation {
    PARENT,
    CHILD,
    LEFT_SIBLING,
    RIGHT_SIBLING
};

// Used to represent the operator type
enum OperatorType {
    PLUS_OP,
    MINUS_OP,
    TIMES_OP,
    DIVISION_OP
};