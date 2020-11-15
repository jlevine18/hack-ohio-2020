#pragma once

#include "GraphNode.h"
#include <map>
class UndirectedWeightedGraphEdge
{
public:
	UndirectedWeightedGraphEdge(GraphNode* node_1_new, GraphNode* node_2_new, double weight_new);
	std::pair<GraphNode*,GraphNode*> GetNodes() const;
	double GetWeight() const;
	bool DoNodesMatch(GraphNode* node_1_test, GraphNode* node_2_test) const;
private:
	GraphNode* node_1;
	GraphNode* node_2;
	double weight;
};

