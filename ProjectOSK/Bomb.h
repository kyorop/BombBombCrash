#pragma once
#define BOMBDEVIDENUMBER 60

class Player;
class Map;

class Bomb
{
	friend class Explosion;
private:
	int x;
	int y;
	int x_center;
	int y_center;
	int graph[BOMBDEVIDENUMBER];
	//int graph_explosion;
	
	int flag;
	//int ExplosionTimer(int time);
	//void SetExplosion(const Map &map);

public:
	Bomb();
	~Bomb();
	void BombSet(const Player &player, const Map &map);
	void Draw();
	
private:
	int Timer(int time);
};

