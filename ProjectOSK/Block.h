#pragma once
#include "MapObstacle.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Player;
class Block:
	public MapObstacle
{
private:
	//int x[MAPSIZE_Y][MAPSIZE_X];
	int rx[MAPSIZE_Y][MAPSIZE_X];
	//int y[MAPSIZE_Y][MAPSIZE_X];
	int dy[MAPSIZE_Y][MAPSIZE_X];
	//int blockID[MAPSIZE_Y][MAPSIZE_X];
	int graph;

public:
	void CheckHit(Player *player);
	void Draw();

	Block(void);
	~Block(void);
};

