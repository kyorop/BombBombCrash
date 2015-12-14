#include "Graph.h"
#include <climits>

using namespace BombBombCrash;

Graph::Graph(void):
	nodeMatrix()
{
}

Graph::Node::Node():
	i_preNode(-1),
	j_preNode(-1),
	minCost(INT_MAX),
	settled(0)
{
}

//Node* Graph::GetNode(int i, int j)
//{
//	return  &nodeMatrix[i][j];
//}

void Graph::Initialize()
{
	for (int i = 0; i < MAPSIZE_Y; i++)
	{
		for (int j = 0; j < MAPSIZE_X; j++)
		{
			nodeMatrix[i][j].i_preNode = -1;
			nodeMatrix[i][j].j_preNode = -1;
			nodeMatrix[i][j].minCost = INT_MAX;
			nodeMatrix[i][j].settled = 0;
		}
	}
}

void Graph::SetCost(int i, int j, int cost)
{
	nodeMatrix[i][j].minCost = cost;
}

int Graph::GetCost(int i, int j)const
{
	return nodeMatrix[i][j].minCost;
}

void Graph::SetPreNode(int i, int j, int i_pre, int j_pre)
{
	nodeMatrix[i][j].i_preNode = i_pre;
	nodeMatrix[i][j].j_preNode = j_pre;
}

int Graph::GetPreNode_i(int i, int j)const
{
	return nodeMatrix[i][j].i_preNode;
}

int Graph::GetPreNode_j(int i, int j)const
{
	return nodeMatrix[i][j].j_preNode;
}

void Graph::SettleShortestPath(int i, int j)
{
	nodeMatrix[i][j].settled = 1;
}

int Graph::GetSettled(int i, int j)const
{
	return nodeMatrix[i][j].settled;
}

Graph::Node::~Node()
{
}

Graph::~Graph(void)
{
}
