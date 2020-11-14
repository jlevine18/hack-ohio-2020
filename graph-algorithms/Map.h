#pragma once
#include "Connection.h"
#include "Node.h"
#include <vector>
class Map
{

public:
	Map();
	void Add_Truck();
	void Add_Node(Node node);
	void Connect_Nodes(Node& n1, Node& n2, int distance);

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

	//Gets the smallest spanning tree. Uses Kruskal's algorithm.
	Map GetMiminimumSpanningTree();


private:
	std::vector<Node> nodes_;
	std::vector<Connection> connections_;
};

