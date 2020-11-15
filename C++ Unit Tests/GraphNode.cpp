#include "pch.h"
#include "GraphNode.h"

GraphNode::GraphNode(std::map<std::string, double> data_new)
{
	data = data_new;
}

GraphNode::GraphNode(const GraphNode& copy)
{
	data = copy.GetData();
}

std::map<std::string, double> GraphNode::GetData() const
{
	return data;
}

void GraphNode::SetData(std::map<std::string, double> data_new)
{
	data = data_new;
}