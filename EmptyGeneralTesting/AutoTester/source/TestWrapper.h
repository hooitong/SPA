#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include "AbstractWrapper.h"
#include "PKB.h"
#include "QueryPreprocessor.h"
#include "QueryEvaluator.h"
#include "SPAFrontEnd.h"

#include <string>
#include <iostream>
#include <list>

// include your other headers here

class TestWrapper : public AbstractWrapper {
  public:
    // default constructor
    TestWrapper();

    // destructor
    ~TestWrapper();

    // method for parsing the SIMPLE source
    virtual void parse(std::string filename);

    // method for evaluating a query
    virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
