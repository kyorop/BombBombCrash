#pragma once
#include "Node.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Graph
{
private:
	//すべてのマスをノードとみる
	Node nodeMatrix[MAPSIZE_Y][MAPSIZE_X];
public:
	//各ノードにアクセスする
	Node* GetNode(int i, int j);
	void Initialize();
	Graph(void);
	virtual ~Graph(void);
};

