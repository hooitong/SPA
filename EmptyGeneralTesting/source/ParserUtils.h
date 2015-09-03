#pragma once

#include "ParsingToken.h"
#include <vector>
#include <sstream>

class ParserUtils {
  public:
	 static bool isNumeric(string aString);
	 static bool isValidName(string aString);
	 static vector<string> &split(const string &s, char delim, vector<string> &elems);
	 static vector<string> split(const string &s, char delim);
	 static void replaceAll( string &s, const string &search, const string &replace );

  private:
	 

};