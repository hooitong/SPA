#pragma once
#include<string>

using namespace std;
typedef string PROC, PROCNAME, VARNAME;
typedef int PROCINDEX, PROGLINE, STMTLINE, VARINDEX, CONSTINDEX;
enum TType {
	PROCEDURE_NODE,
	STMTLST_NODE,
	ASSIGN_NODE,
	VAR_NODE,
	CONST_NODE,
	PLUS_NODE,
	NONE
};