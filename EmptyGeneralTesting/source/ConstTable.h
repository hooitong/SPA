#pragma once
#include <vector>
#include "GlobalType.h"

using namespace std;


class ConstTable
{
public:
	ConstTable(void);
	~ConstTable(void);

	CONSTINDEX insertConst(int constant);
	int getConst(CONSTINDEX index);
	CONSTINDEX getConstIndex(int constant);
	vector<int> getAllConst();

	
};

