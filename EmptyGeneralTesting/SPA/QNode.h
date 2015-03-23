#pragma once
#include <string>
#include <vector>
#include "GlobalTypedef.h"

using namespace std;

class QNode {
private:
	QNodeType type;
	string name;
	vector<QNode*> childrenNodes;

public:
	QNode(void);
	QNode(name, type);
	~QNode(void);

	QNodeType getQType(QNode node);
	string getString(QNode node);
	vector<QNode*> getChildren(QNode node);

	void addChild(QNode* node);
};