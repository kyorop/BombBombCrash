#pragma once
#include "MapObstacle.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Charactor;
class Block:
	public MapObstacle
{
private:
	int graph;

public:
	void CheckHit(Charactor *charactor);
	void Draw();

	Block(void);
	~Block(void);
};

