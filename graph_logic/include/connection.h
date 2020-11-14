#pragma once
namespace graphlogic {
	class Connection {
	public:
		Connection(Node& n1, Node& n2, int enviro, int time, int distance, int cost);
	private:
		Node* n1_;
		Node* n2_;
		int weight_;
	};
}