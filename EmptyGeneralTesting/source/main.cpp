#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "AST.h"

using namespace std;

AST ast();  // global variable

class SyntaxErrorException : public exception
{

};

void parseLine(string line)
{

}

/*
	Remove comment in a line and return a list of tokens from that line
*/
vector<string> tokenizeLine(string line)
{
	vector<string> tokenList;

	string currStr = "";
	for (int i=0; i<line.size(); i++) {
		char nextChar = line.at(i);
		if (nextChar == ' ' || nextChar == '\t') {
			if (currStr.size() > 0) {
				tokenList.push_back(currStr);
				currStr = "";
			}
		} else if (nextChar == '=' || nextChar == '+' || nextChar == ';' || nextChar == '{' || nextChar == '}') {
			if (currStr.size() > 0) {
				tokenList.push_back(currStr);
			}
			tokenList.push_back(string(1, nextChar));
			currStr = "";
		} else if (nextChar == '\\') {
			if (i == line.size() - 1) {
				throw SyntaxErrorException();
			} else if (line.at(i+1) == '\\') {  // Ignore comments
				return tokenList;
			} else {
				throw SyntaxErrorException();
			}
		} else if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') || (nextChar >= '0' && nextChar <= '9')) {
			currStr.push_back(nextChar);
		}
	}

	return tokenList;
}

int main(void)
{
	cout << "Enter name of the source file:";
	string fileName;
	getline(cin, fileName);
	
	ifstream sourceFile(fileName);
	
	string line;
	while (getline(sourceFile, line)) {
		vector<string> tokenList = tokenizeLine(line);
		for (int i=0; i<tokenList.size(); i++) {
			cout << tokenList.at(i) << " ";
		}
		cout << "\n";
	}

	sourceFile.close();

	return 0;
}