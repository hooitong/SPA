#pragma once
#include <vector>

using namespace std;

typedef ConstIndex;

class ConstTable
{
public:
	ConstTable(void);
	~ConstTable(void);

	ConstIndex insertConst(int constant);
	int getConst(ConstIndex index);
	ConstIndex getConstIndex(int constant);
	vector<int> getAllConst();

	
};

