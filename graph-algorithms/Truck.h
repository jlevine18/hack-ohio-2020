#pragma once
#include "Hazard.h"

class Truck
{
public:
	Truck(int resources_, Hazard hazard);
	Truck(int resources_);

	int DropOff(int quantity);

	bool empty();
private:
	int resources_;
	Hazard hazard_;

};

