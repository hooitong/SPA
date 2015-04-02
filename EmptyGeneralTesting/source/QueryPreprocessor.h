
#include "QueryTree.h"
#include <string>
#include <map>
using namespace std;

class QueryPreprocessor {
  public:
    QueryTree* parseQuery(string query);

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
	/*------------------------------------------------*/

	string trim(string s);



	bool checkConditionPositions(string query);
	bool trimAndCheckClause(string clause, int num);
	bool splitAndCheckClause(string clause, int num);
	bool checkAttribute(string attribute);
	bool checkPattern(string pattern);
	bool checkRelation(string relation);
	bool checkWhile(string pattern);
	bool checkIf(string pattern);
	bool checkAssign(string pattern);
	string getType(string synonym);
	bool checkDeclaration(string declaration);
	bool checkExpression(string expression);

  private:
	map<string, int> positions;
	 



};