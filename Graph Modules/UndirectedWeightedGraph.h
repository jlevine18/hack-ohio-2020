#pragma once
#include <vector>
#include<algorithm>
#include <stdexcept>
#include "GraphNode.h"
#include "GraphNode.h"
#include "DisjointSet.h"
#include "UndirectedWeightedGraphEdge.h"
class UndirectedWeightedGraph
{
public:
	UndirectedWeightedGraph();
	UndirectedWeightedGraph(std::vector<GraphNode*> nodes_new, std::vector<UndirectedWeightedGraphEdge*> edges_new);
	~UndirectedWeightedGraph();
	void AddNode(GraphNode* node);
	void AddEdge(UndirectedWeightedGraphEdge* edge);
	std::vector<GraphNode*> GetNodes() const;
	std::vector<UndirectedWeightedGraphEdge*> GetEdges() const;
	UndirectedWeightedGraphEdge GetEdgeBetweenNodes(GraphNode* node1, GraphNode* node2);
	UndirectedWeightedGraph FindMinimumSpanningTree();
private:
	std::vector<GraphNode*> nodes;
	std::vector<UndirectedWeightedGraphEdge*> edges;
};

