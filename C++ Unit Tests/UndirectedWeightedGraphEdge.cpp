#include "pch.h"
#include "UndirectedWeightedGraphEdge.h"

UndirectedWeightedGraphEdge::UndirectedWeightedGraphEdge(GraphNode* node_1_new, GraphNode* node_2_new, double weight_new)
{
	node_1 = node_1_new;
	node_2 = node_2_new;
	weight = weight_new;
}

std::pair<GraphNode*, GraphNode*> UndirectedWeightedGraphEdge::GetNodes() const
{
	return std::pair<GraphNode*, GraphNode*>(node_1, node_2);
}

double UndirectedWeightedGraphEdge::GetWeight() const
{
	return weight;
}

bool UndirectedWeightedGraphEdge::DoNodesMatch(GraphNode* node_1_test, GraphNode* node_2_test) const
{
	return (node_1 == node_1_test && node_2 == node_2_test) || (node_2 == node_1_test && node_1 == node_2_test);
}
