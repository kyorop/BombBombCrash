#include "Node.h"
#include <climits>

Node::Node(void):
	i_preNode(-1),
	j_preNode(-1),
	minCost(INT_MAX),
	settled(0)
	//i(),
	//j()
{
}

void Node::SetComponent(int i, int j)
{

}

Node::~Node(void)
{
}
