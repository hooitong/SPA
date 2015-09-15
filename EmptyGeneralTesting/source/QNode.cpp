#include "QNode.h"

#include <vector>
#include <iostream>

#include "GlobalType.h"

QNode::QNode(void) {
}

QNode::QNode(QNodeType type, string name) {
    this->type = type;
    this->name = name;
}

QNode::~QNode(void) {
}

QNodeType QNode::getQType() {
    return this->type;
}

string QNode::getString() {
    return this->name;
}

vector<QNode*> QNode::getChildren(void) {
    return this->childrenNodes;
}

void QNode::addChild(QNode* node) {
    this->childrenNodes.push_back(node);
}

bool QNode::isEqualSubtree(QNode* node) {
    /*std::cout << node->name << " " << this->name << "            ";
    std::cout << node->type << " " << this->type << "            ";
    std::cout << node->childrenNodes.size() << " " << this->childrenNodes.size() << endl;*/
	if (node == NULL) {
		return false;
	}
    if (this->name != node->name || this->type != node->type) {
        return false;
    }
    if (this->childrenNodes.size() != node->childrenNodes.size()) {
        return false;
    }

	std::vector<bool> chosen((int)node->childrenNodes.size(), false);

	for (int i = 0; i < (int)this->childrenNodes.size(); ++i) {
		bool found = false;
		for (int j = 0; j < (int)node->childrenNodes.size(); ++j) {
			if (chosen[j]) {
				continue;
			}
			if (this->childrenNodes[i]->isEqualSubtree(node->childrenNodes[j])) {
				found = true;
				chosen[j] = true;
				break;
			}
		}
		if (!found) {
			return false;
		}
	}
	return true;

    for (int i = 0; i < (int)node->childrenNodes.size(); ++i) {
        if (!(this->childrenNodes[i])->isEqualSubtree(node->childrenNodes[i])) {
            return false;
        }
    }
    return true;
}