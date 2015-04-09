#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include <fstream>
#include <SPAFrontEnd.h>

using namespace std;

int main(int argc, char* argv[]) {
    // Get the top level suite from the registry

    CppUnit::TestSuite *suite = new CppUnit::TestSuite("All integration tests");

	// Calls SPA Front-End to Parse Integration Test File
	SPAFrontEnd::getInstance()->parseSource("integration.txt");

    suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserFollowsTest").makeTest());
    suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserParentTest").makeTest());
    suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserModifiesTest").makeTest());
    suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserUsesTest").makeTest());

    CppUnit::TestFactoryRegistry::getRegistry().addTestToSuite(suite);
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(suite);
    bool wasSucessful = runner.run();

    getchar();

    return wasSucessful ? 0 : 1;
}