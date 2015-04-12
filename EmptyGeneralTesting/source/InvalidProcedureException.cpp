#include "InvalidProcedureException.h"

InvalidProcedureException::InvalidProcedureException() {

}

InvalidProcedureException::~InvalidProcedureException() {

}

string InvalidProcedureException::message() {
	return "Invalid procedure ";
}