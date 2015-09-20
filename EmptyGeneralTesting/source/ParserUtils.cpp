#include "ParserUtils.h"



bool ParserUtils::isNumeric(string aString) {
  for (int i = 0; i < aString.size(); i++) {
    if (aString.at(i) < '0' || aString.at(i) > '9')
      return false;
  }
  return true;
}

bool ParserUtils::isValidName(string aString) {
  if (aString.size() == 0)
    return false;
  else if (aString.compare("while") == 0 || aString.compare("if") == 0
    || aString.compare("else") == 0 || aString.compare("procedure") == 0) {
    // name cannot be one of reserved words
    return false;
  }
  else {
    if (aString.at(0) < 'A' || (aString.at(0) > 'Z' && aString.at(0) < 'a') || (aString.at(0) > 'z')) {
      // first character is not a letter
      return false;
    }
    else {
      for (int i = 1; i < aString.size(); i++) {
        if ((aString.at(i) >= '0' && aString.at(i) <= '9') || (aString.at(i) >= 'a' && aString.at(i) <= 'z')
          || (aString.at(i) >= 'A' && aString.at(i) <= 'Z')) {
          // if ith character is a digit or a letter, then continue
        }
        else {
          return false;
        }
      }
      return true;
    }
  }
}

bool ParserUtils::isValidNameOrNumeric(string aString) {
  return ParserUtils::isValidName(aString) || ParserUtils::isNumeric(aString);
}

vector<string> ParserUtils::split(const string &s, char delim) {
  vector<std::string> elems;
  ParserUtils::split(s, delim, elems);
  return elems;
}

vector<string> &ParserUtils::split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    if (item != "") {
      elems.push_back(item);
    }
  }
  return elems;
}

void ParserUtils::replaceAll(string &s, const string &search, const string &replace) {
  for (size_t pos = 0; ; pos += replace.length()) {
    // Locate the substring to replace
    pos = s.find(search, pos);
    if (pos == string::npos) break;
    // Replace by erasing and inserting
    s.erase(pos, search.length());
    s.insert(pos, replace);
  }
}


