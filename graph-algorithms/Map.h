#pragma once
#include "MapNode.h"
#include "Connection.h"
#include <vector>
class Map
{
public:
	Map();
	void Add_Truck();
	void Add_Node();
	void Connect_Nodes();

	// --- Big 5 ---
	// Copy constructor.
	Map(const Map& source);
	// Move constructor.
	Map(Map&& source) noexcept;
	// Destructor.
	~Map();
	// Copy assignment operator.
	Map& operator=(const Map& source);
	// Move assignment operator.
	Map& operator=(Map&& source) noexcept;


private:
	std::vector<MapNode> nodes;
	std::vector<Connection> connections;
};

