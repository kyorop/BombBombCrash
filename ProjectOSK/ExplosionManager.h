#pragma once
#include <vector>
#include "Timer.h"
class Explosion;
class Bomb;
class MapObstacle;
class Player;
class ItemManager;
class BombManager;
class Charactor;
class Item;
class ExplosionManager
{
private:
	int nowFireLevel;
	int fuse;
	int explosion;
	Timer retainFire;
	Timer beforeExplosion;
	static const int displayingTime = 200; 
	const int image_fire;
	std::vector<Explosion*> vex;

public:
	int GetX(int i)const;
	int GetRX(int i)const;
	int GetY(int i)const;
	int GetDY(int i)const;
	int GetFlag(int i)const;
	void SetFlag(int i, int flag);
	int GetSize()const;
	void FireUp();	
	void Update(const Bomb &bomb);
	void Maintain();
	void Draw();
	ExplosionManager();
	~ExplosionManager(void);


	void SetFuse(int flag);
	void Register(void);
	int GetExplosion(void);
	int GetFireLevel(void);
};

