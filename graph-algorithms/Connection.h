#pragma once
#include "MapNode.h"
class Connection
{

public:
	Connection(MapNode& n1, MapNode& n2, int enviro, int time, int distance, int cost);
private:
	MapNode* n1_;
	MapNode* n2_;
	int weight_;

};

