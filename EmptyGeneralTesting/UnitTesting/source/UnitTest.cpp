#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;

int main(int argc, char* argv[]) {
  // Get the top level suite from the registry
  CppUnit::TestSuite* unitSuite = new CppUnit::TestSuite("All unit test");

  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("GrammarTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TokenizerTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ASTTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("DesignExtractorTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("FollowsTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ModifiesTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParentTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParserTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("QueryEvaluatorTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("QueryPreprocessorTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("QueryResultTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("QueryTreeTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("TNodeTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("UsesTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("VarTableTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("CFGTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("CallsEvaluatorTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("CallsStarEvaluatorTest").makeTest());
  unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("WithEvaluatorTest").makeTest());

  CppUnit::TestFactoryRegistry::getRegistry().addTestToSuite(unitSuite);
  CppUnit::TextUi::TestRunner runner;

  runner.addTest(unitSuite);
  bool wasSuccessful = runner.run();

  getchar();

  return wasSuccessful?0:1;
}