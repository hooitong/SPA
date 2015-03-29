#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include <fstream>
#include <Parser.h>

using namespace std;

int main(int argc, char* argv[])
{
	// Get the top level suite from the registry
	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
	CppUnit::TextUi::TestRunner runner;

	//parse the SIMPLE soource code into the parser
	//Parse();

	//Call of DesignExtractor
	//Extract();

	runner.addTest(suite);
	bool wasSucessful = runner.run();

	//getchar();

	// test parser
	/*cout << "Enter name of the source file:";
	string fileName;
	getline(cin, fileName);
	ifstream sourceFile(fileName);

	string line;
	while (getline(sourceFile, line)) {
		vector<string> tokenList = Parser::tokenizeLine(line);
		for (int i=0; i<tokenList.size(); i++) {
			cout << tokenList.at(i) << " ";
		}
		cout << "\n";
	}

	sourceFile.close();*/

	/*while (true) {
		cout << "Enter a string: ";
		string aString;
		getline(cin, aString);
		if (Parser::isNumeric(aString)) {
			cout << "is numeric\n";
		} else {
			cout << "is not numeric\n";
		}
		if (Parser::isValidName(aString)) {
			cout << "is a valid name\n";
		} else {
			cout << "is not a valid name\n";
		}
	}*/

	return wasSucessful ? 0 : 1;
}