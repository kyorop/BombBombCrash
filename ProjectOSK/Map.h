#pragma once
#include "MapObstacle.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13
#define MAPCHIPNUM 3

class Map:
	public MapObstacle
{
	friend class Explosion;
	friend class Player;
	friend class Bomb;

private:
	//int x[MAPSIZE_Y][MAPSIZE_X];
	int rx[MAPSIZE_Y][MAPSIZE_X];
	//int y[MAPSIZE_Y][MAPSIZE_X];
	int dy[MAPSIZE_Y][MAPSIZE_X];
	int graph[MAPCHIPNUM];
	int width;
	int height;

public:
	void DrawMap();
	Map(void);
	~Map(void);
};

