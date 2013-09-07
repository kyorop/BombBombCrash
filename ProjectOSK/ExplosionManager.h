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
	void FireUp(const ItemManager &manageItem);	
	void Set(Bomb &bomb);
	void Maintain();
	void CheckHitObject(MapObstacle *mapobstacle);
	void CheckHitCharactor(Charactor *charactor);
	void CheckHitBomb(Bomb *bomb);
	void Draw();
	//void SetFlag(firestate flag);
	ExplosionManager();
	~ExplosionManager(void);


std::vector<Explosion*> *vex;//vectorクラスのオブジェクト生成





};

