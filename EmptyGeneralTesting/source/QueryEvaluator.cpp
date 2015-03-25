#include "QueryEvaluator.h"

string QueryEvaluator::evaluate(QueryTree* query) {
    return "Incomplete Stub Method";
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Follows(TType firstType, TType secondType) {
	// retrieve all stmt# from AST that belongs to the firstType
		

	// retrieve all stmt# from AST that belongs to the secondType


	// double for loop based on both vector of stmt#, check Follows is true then keep into vector as tuple.


}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Parent(TType firstType, TType secondType) {
	// retrieve all stmt# from AST that belongs to the firstType

	// retrieve all stmt# from AST that belongs to the secondType

	// double for loop based on both vector of stmt#, check Follows is true then keep into vector as tuple.

	// return the vector of tuples
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Modifies(TType firstType) {
	// retrieve all stmt# from AST that belongs to the firstType

	// for each stmt#, store all combination tuple of the # and var that it modifies

	// return the vector of tuples
}

vector<std::pair<STMTLINE, STMTLINE>> QueryEvaluator::Uses(TType firstType) {
	// retrieve all stmt# from AST that belongs to the firstType

	// for each stmt#, store all combination tuple of the # and var that it uses

	// return the vector of tuples
}
