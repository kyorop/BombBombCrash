#pragma once
#include "Object.h"
#include "Key.h"
#include "Timer.h"
#define BOMBDEVIDENUMBER 60

class Player;
class Map;
class Charactor;
class Bomb:
	public Object
{
	friend class Explosion;
private:
	int count;
	int graph[BOMBDEVIDENUMBER];
	int explosion;
	Key key;
	Timer time;
public:
	Bomb();
	~Bomb();
	void BombSet(const Charactor &charactor);
	void Draw();
	void MaintainBomb();
	int CheckBombExplosion();
};

