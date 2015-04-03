
#include "QueryTree.h"
#include <string>
#include <map>
using namespace std;

class QueryPreprocessor {
  public:
    QueryTree* parseQuery(string query);
	 QueryPreprocessor(void);
    ~QueryPreprocessor(void);

	struct entity{
		string type;
		string synonym;
	};

	vector<entity> refDeclared;

	/*--------------------checking -------------------*/
	bool checkAttributeName(string attName);
	bool checkIdent(string ident);
	bool checkInteger(string number);
	bool checkAttReference(string attReference);
	bool checkElem(string elem);
	bool checkVarReference(string varReference);
	bool checkDesignEntity(string entity);
	bool checkTuple(string tuple);
	bool existsRef(string reference);

	bool checkFactor(string factor);

	/*------------------------------------------------*/

	string trim(string s);



	bool checkConditionExists(string query);
	bool trimAndCheckClause(string clause, int num);
	bool splitAndCheckClause(string clause, int num);
	bool checkAttribute(string attribute);
	bool checkPattern(string pattern);
	bool checkRelation(string relation);
	bool checkWhile(string pattern);
	bool checkIf(string pattern);
	bool checkAssign(string pattern, string patternName);
	string getType(string synonym);
	bool checkDeclaration(string declaration);
	bool checkExpression(string expression);
	void buildTable();
	int findIndexOfTable(string relationType);
	int findIndexOfType(string type);

  private:
	map<int, int> posOfConds;
	int table[5][24];
	QueryTree tree;
	 



};