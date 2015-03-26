#pragma once
#include "QueryTree.h"
#include <string>
using namespace std;

class QueryPreprocessor {
  public:
    QueryTree* parseQuery(string query);
};