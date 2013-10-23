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
	Timer time;
public:
	//void SetExplosion(const BombManager &bombManager);
	void FireUp();	
	void Set(int x, int y);
	void Maintain();
	void CheckHitObject(MapObstacle *mapobstacle);
	void CheckHitCharactor(Charactor *charactor);
	void CheckHitBomb(Bomb *bomb);
	void CheckHitItem(Item *item);
	void CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager);
	void Draw();
	//void SetFlag(firestate flag);
	ExplosionManager();
	~ExplosionManager(void);

std::vector<Explosion*> vex;//vectorクラスのオブジェクト生成

void SetFuse(int flag);
void Register(void);
};

