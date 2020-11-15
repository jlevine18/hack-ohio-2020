#pragma once
#include "pch.h"
#include <map>
template <typename T>
class DisjointSet
{
public:
	DisjointSet();
	~DisjointSet();
	void AddValue(const T& value);
	T Find(const T& value) const;
	bool CheckDisjoint(const T& val1, const T& val2) const;
	void Union(const T& val1, const T& val2);
private:
	template <typename T>
	struct Node
	{
		Node<T>* parent;
		T value;
		size_t rank;

		Node(T new_value) {
			value = new_value;
			parent = nullptr;
			rank = 0;
		}
	};

	std::map<T, Node<T>*> nodes;
	T FindFromNode(Node<T>* node) const;

};

template<typename T>
inline DisjointSet<T>::DisjointSet()
{
}

template<typename T>
inline DisjointSet<T>::~DisjointSet()
{
	for (auto location : nodes) {
		delete location.second;
	}
}

template<typename T>
inline void DisjointSet<T>::AddValue(const T& value)
{
	nodes.insert(std::pair<T, Node<T>*>(value, new Node<T>(value)));
}

template<typename T>
inline T DisjointSet<T>::Find(const T& value) const
{
	Node<T>* current = nodes.find(value)->second;
	Node<T>* parent = current->parent;
	if (parent == nullptr) {
		return value;
	}
	else {
		return FindFromNode(current);
	}
}

template<typename T>
inline bool DisjointSet<T>::CheckDisjoint(const T& val1, const T& val2) const
{
	return Find(val1) != Find(val2);
}

template<typename T>
inline void DisjointSet<T>::Union(const T& val1, const T& val2)
{
	T root_1 = Find(val1);
	T root_2 = Find(val2);
	Node<T>& node_root_1 = *(nodes.find(root_1)->second);
	Node<T>& node_root_2 = *(nodes.find(root_2)->second);

	if (node_root_1.value != node_root_2.value) {
		if (node_root_1.rank > node_root_2.rank) {
			node_root_2.parent = &node_root_1;
		}
		else if (node_root_2.rank > node_root_1.rank) {
			node_root_1.parent = &node_root_2;
		}
		else {
			node_root_2.parent = &node_root_1;
			node_root_1.rank++;
		}
	}
}

template<typename T>
inline T DisjointSet<T>::FindFromNode(Node<T>* node) const
{
	return node->parent == nullptr ? node->value : FindFromNode(node->parent);
}
