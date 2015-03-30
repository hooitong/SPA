#pragma once
using namespace std;
#include <vector>
#include <map>
#include "GlobalType.h"
#include "TNode.h"
class DivisionByZeroException{
		public:
				DivisionByZeroException()
						: message("Division by zero error!"){}
				const char * what() const{ return message;}
		private:
				const char * message;
};
