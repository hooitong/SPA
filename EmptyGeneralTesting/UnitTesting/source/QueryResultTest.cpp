#include <cppunit/config/SourcePrefix.h>

#include "QueryResultTest.h"

#include "QueryResult.h"

void QueryResultTest::setUp() {
}

void QueryResultTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(QueryResultTest);

void QueryResultTest::testEqual() {
    vector <string> synonym1;
    synonym1.push_back("a");
    synonym1.push_back("b");
    synonym1.push_back("c");
    QueryResult one(synonym1);

    vector <string> synonym2;
    synonym2.push_back("a");
    synonym2.push_back("b");
    synonym2.push_back("c");
    QueryResult two(synonym2);

    vector <int> result1;
    result1.push_back(5);
    result1.push_back(2);
    result1.push_back(3);

    vector <int> result2;
    result2.push_back(2);
    result2.push_back(6);
    result2.push_back(7);

    one.addSolution(result1);
    one.addSolution(result2);

    two.addSolution(result1);
    two.addSolution(result2);

    CPPUNIT_ASSERT(one == two);
}

void QueryResultTest::testDifferent() {
    vector <string> synonym1;
    synonym1.push_back("a");
    synonym1.push_back("b");
    synonym1.push_back("c");
    QueryResult one(synonym1);

    vector <string> synonym2;
    synonym2.push_back("c");
    synonym2.push_back("a");
    synonym2.push_back("asdf");
    QueryResult two(synonym2);


    vector <int> result1;
    result1.push_back(5);
    result1.push_back(2);
    result1.push_back(3);

    vector <int> result2;
    result2.push_back(2);
    result2.push_back(6);
    result2.push_back(7);

    vector <int> result1reorder;
    result1reorder.push_back(3);
    result1reorder.push_back(5);
    result1reorder.push_back(2);

    vector <int> result2reorder;
    result2reorder.push_back(7);
    result2reorder.push_back(2);
    result2reorder.push_back(6);

    one.addSolution(result1);
    one.addSolution(result2);

    two.addSolution(result2reorder);
    two.addSolution(result1reorder);

    CPPUNIT_ASSERT(!(one == two));
}

void QueryResultTest::testEqualReorder() {
    vector <string> synonym1;
    synonym1.push_back("a");
    synonym1.push_back("b");
    synonym1.push_back("c");
    QueryResult one(synonym1);

    vector <string> synonym2;
    synonym2.push_back("c");
    synonym2.push_back("a");
    synonym2.push_back("b");
    QueryResult two(synonym2);


    vector <int> result1;
    result1.push_back(5);
    result1.push_back(2);
    result1.push_back(3);

    vector <int> result2;
    result2.push_back(2);
    result2.push_back(6);
    result2.push_back(7);

    vector <int> result1reorder;
    result1reorder.push_back(3);
    result1reorder.push_back(5);
    result1reorder.push_back(2);

    vector <int> result2reorder;
    result2reorder.push_back(7);
    result2reorder.push_back(2);
    result2reorder.push_back(6);

    one.addSolution(result1);
    one.addSolution(result2);

    two.addSolution(result2reorder);
    two.addSolution(result1reorder);

    CPPUNIT_ASSERT(one == two);
}

void QueryResultTest::testFirstEmptySynonym() {
    vector <string> synonym1;
    QueryResult one(synonym1);
    vector <int> emptyResult;
    one.addSolution(emptyResult);

    vector <string> synonym2;
    synonym2.push_back("a");
    synonym2.push_back("b");
    synonym2.push_back("c");
    QueryResult two(synonym2);

    vector<int> resulttwo1;
    resulttwo1.push_back(1);
    resulttwo1.push_back(2);
    resulttwo1.push_back(3);

    vector<int> resulttwo2;
    resulttwo2.push_back(4);
    resulttwo2.push_back(6);
    resulttwo2.push_back(5);

    two.addSolution(resulttwo1);
    two.addSolution(resulttwo2);

    QueryResult result = one.merge(two);

    QueryResult expected = QueryResult(synonym2);
    expected.addSolution(resulttwo1);
    expected.addSolution(resulttwo2);

    CPPUNIT_ASSERT(expected == result);
}


void QueryResultTest::testSecondEmptySynonym() {
    vector <string> synonym1;
    synonym1.push_back("a");
    synonym1.push_back("b");
    synonym1.push_back("c");
    QueryResult one(synonym1);

    vector<int> resultone1;
    resultone1.push_back(1);
    resultone1.push_back(2);
    resultone1.push_back(3);

    vector<int> resultone2;
    resultone2.push_back(4);
    resultone2.push_back(6);
    resultone2.push_back(5);

    one.addSolution(resultone1);
    one.addSolution(resultone2);

    vector <string> synonym2;
    QueryResult two(synonym2);

    vector <int> emptyResult;
    two.addSolution(emptyResult);

    QueryResult result = one.merge(two);

    QueryResult expected = QueryResult(synonym1);
    expected.addSolution(resultone1);
    expected.addSolution(resultone2);

    CPPUNIT_ASSERT(expected == result);
}

void QueryResultTest::testMultipleMerge() {
    vector <string> synonym1;
    synonym1.push_back("a");
    synonym1.push_back("b");
    synonym1.push_back("c");
    synonym1.push_back("d");
    QueryResult one(synonym1);

    vector<int> resultone1;
    resultone1.push_back(1);
    resultone1.push_back(2);
    resultone1.push_back(3);
    resultone1.push_back(4);

    vector<int> resultone2;
    resultone2.push_back(4);
    resultone2.push_back(6);
    resultone2.push_back(5);
    resultone2.push_back(7);

    vector <int> resultone3;
    resultone3.push_back(1);
    resultone3.push_back(2);
    resultone3.push_back(10);
    resultone3.push_back(11);

    one.addSolution(resultone1);
    one.addSolution(resultone2);
    one.addSolution(resultone3);

    vector <string> synonym2;
    synonym2.push_back("b");
    synonym2.push_back("a");
    synonym2.push_back("e");
    synonym2.push_back("f");
    QueryResult two(synonym2);

    vector<int> resulttwo1;
    resulttwo1.push_back(2);
    resulttwo1.push_back(1);
    resulttwo1.push_back(10);
    resulttwo1.push_back(9);

    vector <int> resulttwo2;
    resulttwo2.push_back(2);
    resulttwo2.push_back(1);
    resulttwo2.push_back(3);
    resulttwo2.push_back(10);

    vector<int> resulttwo3;
    resulttwo3.push_back(6);
    resulttwo3.push_back(5);
    resulttwo3.push_back(10);
    resulttwo3.push_back(9);

    two.addSolution(resulttwo1);
    two.addSolution(resulttwo2);
    two.addSolution(resulttwo3);


    QueryResult result = one.merge(two);

    vector <string> expectedSynonyms;
    expectedSynonyms.push_back("a");
    expectedSynonyms.push_back("b");
    expectedSynonyms.push_back("c");
    expectedSynonyms.push_back("d");
    expectedSynonyms.push_back("e");
    expectedSynonyms.push_back("f");

    vector <int> expected1;
    expected1.push_back(1);
    expected1.push_back(2);
    expected1.push_back(3);
    expected1.push_back(4);
    expected1.push_back(10);
    expected1.push_back(9);

    vector <int> expected2;
    expected2.push_back(1);
    expected2.push_back(2);
    expected2.push_back(3);
    expected2.push_back(4);
    expected2.push_back(3);
    expected2.push_back(10);

    vector <int> expected3;
    expected3.push_back(1);
    expected3.push_back(2);
    expected3.push_back(10);
    expected3.push_back(11);
    expected3.push_back(10);
    expected3.push_back(9);

    vector <int> expected4;
    expected4.push_back(1);
    expected4.push_back(2);
    expected4.push_back(10);
    expected4.push_back(11);
    expected4.push_back(3);
    expected4.push_back(10);

    QueryResult expected = QueryResult(expectedSynonyms);
    expected.addSolution(expected1);
    expected.addSolution(expected2);
    expected.addSolution(expected4);
    expected.addSolution(expected3);

    CPPUNIT_ASSERT(expected == result);
}

void QueryResultTest::testFilter() {
    vector <string> synonym1;
    synonym1.push_back("a");
    synonym1.push_back("b");
    synonym1.push_back("c");
    synonym1.push_back("d");
    QueryResult one(synonym1);

    vector<int> resultone1;
    resultone1.push_back(1);
    resultone1.push_back(2);
    resultone1.push_back(3);
    resultone1.push_back(4);

    vector<int> resultone2;
    resultone2.push_back(4);
    resultone2.push_back(6);
    resultone2.push_back(5);
    resultone2.push_back(7);

    vector <int> resultone3;
    resultone3.push_back(1);
    resultone3.push_back(2);
    resultone3.push_back(10);
    resultone3.push_back(11);

    one.addSolution(resultone1);
    one.addSolution(resultone2);
    one.addSolution(resultone3);

    vector <string> expectedSynonym;
    expectedSynonym.push_back("b");
    expectedSynonym.push_back("a");
    QueryResult expected(expectedSynonym);

    vector <int> expected1;
    expected1.push_back(2);
    expected1.push_back(1);

    vector <int> expected2;
    expected2.push_back(6);
    expected2.push_back(4);

    expected.addSolution(expected1);
    expected.addSolution(expected2);

    CPPUNIT_ASSERT(one.filter(expectedSynonym) == expected);
}