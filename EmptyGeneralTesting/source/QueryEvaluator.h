#pragma once

#include <string>
#include <vector>

#include "PKB.h"
#include "QueryTree.h"


class QueryEvaluator {
  public:
    string evaluate(QueryTree* tree);

// Handle evaluation with wildcards of a certain type. (May be relocated in the future)
  private:
    PKB pkbInstance; //Stub instance for coding. Need to have instance accessible by Query System.
    vector<std::pair<STMTLINE, STMTLINE>> Follows(TType firstType, TType secondType);
    vector<std::pair<STMTLINE, STMTLINE>> Parent(TType firstType, TType secondType);
    vector<std::pair<STMTLINE, VARINDEX>> Modifies(TType firstType); // get all tuples of the type + var that it modifies
    vector<std::pair<STMTLINE, VARINDEX>> Uses(TType firstType); // get all tuples of the type + var that it uses
};