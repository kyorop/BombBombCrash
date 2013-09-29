#include "Graph.h"


Graph::Graph(void):
	nodeMatrix()
{
}

Node* Graph::GetNode(int i, int j)
{
	return  &nodeMatrix[i][j];
}

void Graph::Initialize()
{
	for (int i = 0; i < MAPSIZE_Y; i++)
	{
		for (int j = 0; j < MAPSIZE_X; j++)
		{
			nodeMatrix[i][j].Initialize();
		}
	}
}

Graph::~Graph(void)
{
}
