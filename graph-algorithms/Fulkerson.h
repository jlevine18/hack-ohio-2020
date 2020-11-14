#pragma once
#include "Map.h"

class Fulkerson
{
public:
	Fulkerson(Map& map);

	void SetWeights(int enviro, int cost, int distance, int time);

	void RunModel();

private:

	
};

