#include "Node.h"
#include <climits>

Node::Node(void):
	i_preNode(-1),
	j_preNode(-1),
	minCost(INT_MAX),
	settled(0)
{
}

void Node::Initialize()
{
	i_preNode = -1;
	j_preNode = -1;
	minCost = INT_MAX;
	settled = 0;
}

void Node::SetCost(int cost)
{
	minCost = cost;
}

int Node::GetCost()const
{
	return minCost;
}

void Node::SetPreNode(int i_pre, int j_pre)
{
	i_preNode = i_pre;
	j_preNode = j_pre;
}

void Node::SettleShortestPath()
{
	settled = 1;
}

int Node::GetSettled()const
{
	return settled;
}

Node::~Node(void)
{
}
