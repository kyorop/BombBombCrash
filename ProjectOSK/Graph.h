#pragma once
#include "Node.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Graph
{
private:
	Node node[MAPSIZE_Y][MAPSIZE_X];
public:
	Graph(void);
	~Graph(void);
};

