#pragma once
#include <map>
#include <vector>
#include <string>
#include <exception>
#include "GlobalType.h"

class Parser {
  public:
    Parser(void);
    ~Parser(void);
    static vector<string> tokenizeLine(string line);
};