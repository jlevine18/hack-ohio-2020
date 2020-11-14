#pragma once
#include "Node.h"
class Connection
{

public:
	Connection(Node& n1, Node& n2, int weight);
private:
	Node* n1_;
	Node* n2_;
	int weight_;

};

