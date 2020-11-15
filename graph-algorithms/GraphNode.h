#pragma once

#include <map>
#include <string>
class GraphNode
{
public:
	GraphNode(std::map<std::string, double> data_new);
	GraphNode(const GraphNode& copy);
	std::map<std::string, double> GetData() const;
	void SetData(std::map<std::string, double> data_new);
private:
	std::map<std::string, double> data;
};

