#pragma once
#include "pch.h"
#include<string>
#include<map>
class GraphNode
{
public:
	GraphNode(std::map<std::string, double> data_new);
	GraphNode::GraphNode(const GraphNode& copy);
	std::map<std::string, double> GraphNode::GetData() const;
	void GraphNode::SetData(std::map<std::string, double> data_new);
private:
	std::map<std::string, double> data;
	


};

