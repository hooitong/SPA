#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <fstream>

#include "SPAFrontEnd.h"

using namespace std;

int main(int argc, char* argv[]) {
  // Get the top level suite from the registry
  CppUnit::TestSuite *suite = new CppUnit::TestSuite("All integration tests");

  // Calls SPA Front-End to Parse Integration Test File
  if (argc == 1) {
    SPAFrontEnd::getInstance()->parseSource("integration.txt");
  }
  else {
    SPAFrontEnd::getInstance()->parseSource(argv[1]);
  }
  
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserConstTableTest").makeTest());
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserFollowsTest").makeTest());
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserParentTest").makeTest());
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserModifiesTest").makeTest());
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserUsesTest").makeTest());
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserPatternTest").makeTest());
  suite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserCallsTest").makeTest());

  CppUnit::TestFactoryRegistry::getRegistry().addTestToSuite(suite);
  CppUnit::TextUi::TestRunner runner;

  runner.addTest(suite);
  bool wasSucessful = runner.run();

  getchar();

  return wasSucessful?0:1;
}