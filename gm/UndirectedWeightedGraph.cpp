#include "UndirectedWeightedGraph.h"


UndirectedWeightedGraph::UndirectedWeightedGraph()
{
}

UndirectedWeightedGraph::UndirectedWeightedGraph(std::vector<GraphNode*> nodes_new, std::vector<UndirectedWeightedGraphEdge*> edges_new)
{
	nodes = nodes_new;
	edges = edges_new;
}

UndirectedWeightedGraph::~UndirectedWeightedGraph()
{
	for (GraphNode* node : nodes) {
		delete node;
	}
	for (UndirectedWeightedGraphEdge* edge : edges) {
		delete edge;
	}
}

void UndirectedWeightedGraph::AddNode(GraphNode* node)
{
	nodes.push_back(node);
}

void UndirectedWeightedGraph::AddEdge(UndirectedWeightedGraphEdge* edge)
{
	edges.push_back(edge);
}

std::vector<GraphNode*> UndirectedWeightedGraph::GetNodes() const
{
	return nodes;
}

std::vector<UndirectedWeightedGraphEdge*> UndirectedWeightedGraph::GetEdges() const
{
	return edges;
}

UndirectedWeightedGraphEdge UndirectedWeightedGraph::GetEdgeBetweenNodes(GraphNode* node1, GraphNode* node2)
{
	for (auto edge : edges) {
		if (edge->DoNodesMatch(node1, node2)) {
			return *edge;
		}
	}
	throw std::invalid_argument("there is no edge between the nodes");
}

UndirectedWeightedGraph UndirectedWeightedGraph::FindMinimumSpanningTree()
{
	DisjointSet<GraphNode*> disjoint_set;
	std::map<GraphNode*, GraphNode*> old_new_map;
	std::vector<GraphNode*> new_nodes;
	for (auto node : nodes) {
		GraphNode* new_node = new GraphNode(*node);
		new_nodes.push_back(new_node);
		old_new_map.insert(std::pair<GraphNode*, GraphNode*>(node, new_node));
		disjoint_set.AddValue(node);
	}
	std::vector<UndirectedWeightedGraphEdge*> edges_sorted = edges;
	std::sort(edges_sorted.begin(), edges_sorted.end(), [](UndirectedWeightedGraphEdge* edge1, UndirectedWeightedGraphEdge* edge2) {return edge1->GetWeight() < edge2->GetWeight(); });
	std::vector<UndirectedWeightedGraphEdge*> edges_used;
	for (UndirectedWeightedGraphEdge* edge : edges_sorted) {
		std::pair<GraphNode*, GraphNode*> nodes = edge->GetNodes();
		if (disjoint_set.CheckDisjoint(nodes.first, nodes.second)) {
			edges_used.push_back(new UndirectedWeightedGraphEdge(old_new_map.find(nodes.first)->second, old_new_map.find(nodes.second)->second, edge->GetWeight()));
			disjoint_set.Union(nodes.first, nodes.second);
		}
	}

	return UndirectedWeightedGraph(new_nodes, edges_used);
}
