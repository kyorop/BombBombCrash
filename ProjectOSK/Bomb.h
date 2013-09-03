#pragma once
#include "Object.h"
#include "Key.h"
#define BOMBDEVIDENUMBER 60

class Player;
class Map;
class Charactor;
class Bomb:
	public Object
{
	friend class Explosion;
private:
	//int x;
	//int y;
	int graph[BOMBDEVIDENUMBER];
	int explosion;
	//int flag;
	Key key;

public:
	Bomb();
	~Bomb();
	void BombSet(const Charactor &charactor);
	void Draw();
	void MaintainBomb(int time);
	int CheckBombExplosion();

private:
	int Timer(int time);
};

