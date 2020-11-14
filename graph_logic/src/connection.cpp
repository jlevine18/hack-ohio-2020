#include "..\include\connection.h"

graphlogic::Connection::Connection(Node& n1, Node& n2, int weight)
{
	n1_ = n1;
	n2_ = n2;
	weight_ = weight;
}
