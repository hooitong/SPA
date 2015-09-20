#pragma once

#include "Parser.h"
#include "DesignExtractor.h"

class SPAFrontEnd {
private:
  static SPAFrontEnd* feObj;
  DesignExtractor* deObj;

public:
  SPAFrontEnd();
  ~SPAFrontEnd();
  static SPAFrontEnd* getInstance();
  void parseSource(const std::string fileName);
};