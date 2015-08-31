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
    STMTN,
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
	CONDITIONLIST,
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