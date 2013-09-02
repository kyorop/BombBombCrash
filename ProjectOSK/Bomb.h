#pragma once
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

public:
	Bomb();
	~Bomb();
	void BombSet(const Charactor &charactor, const Map &map);
	void Draw();
	int CheckBombExplosion();

private:
	int Timer(int time);
};

