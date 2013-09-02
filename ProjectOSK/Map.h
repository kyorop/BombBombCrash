#pragma once
#include "MapObstacle.h"

class Charactor;
class Map:
	public MapObstacle
{
	friend class Explosion;
	friend class Bomb;

private:
	int graph[2];

public:
	void CheckHitCharactor(Charactor *charactor);
	void Draw();
	Map(void);
	~Map(void);
};

