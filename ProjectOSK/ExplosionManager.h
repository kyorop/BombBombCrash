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
	int addFireNum;
	int nowFireLevel;
	int fuse;
	int explosion;
	Timer retainFire;
	Timer beforeExplosion;
	static const int timeBeforeExplosion = 3000;
	static const int displayingTime = 200; 
	int fireImage;
public:
	//void SetExplosion(const BombManager &bombManager);
	void FireUp();	
	void Set(int x, int y);
	void Maintain();
	//void CheckHitObject(MapObstacle *mapobstacle);
	//void CheckHitCharactor(Charactor *charactor);
	//void CheckHitBomb(Bomb *bomb);
	//void CheckHitItem(Item *item);
	//void CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager);
	void Draw();
	ExplosionManager();
	~ExplosionManager(void);

std::vector<Explosion*> vex;

void SetFuse(int flag);
void Register(void);
};

