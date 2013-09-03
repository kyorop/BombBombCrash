#pragma once
#include "Key.h"
#define BOMBDEVIDENUMBER 60

class Player;
class Map;
class Charactor;
class Bomb
{
	friend class Explosion;
private:
	int x;
	int y;
	int graph[BOMBDEVIDENUMBER];
	int explosion;
	int flag;
	Key key;

public:
	Bomb();
	~Bomb();
	void BombSet(const Charactor &charactor);
	void Draw();
	int CheckBombExplosion();

private:
	int Timer(int time);
};

