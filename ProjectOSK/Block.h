#pragma once
#include "MapObstacle.h"
#include "IDrawable.h"
#include "IRegister.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Charactor;
class Block:
	public MapObstacle, virtual public IDrawable, virtual public IRegister
{
private:
	int graph;

public:
	Block(void);
	~Block(void);
	
	void CheckHit(Charactor *charactor);
	void Register();
	void Draw();


};

