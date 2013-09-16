#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"

class Charactor;
class Map:
	public MapObstacle, virtual public IDrawable, virtual public IRegister
{
	friend class Explosion;
	friend class Bomb;

private:
	int graph[2];

public:
	void CheckHitCharactor(Charactor *charactor);
	void Register();
	void Draw();
	Map(void);
	~Map(void);
};

