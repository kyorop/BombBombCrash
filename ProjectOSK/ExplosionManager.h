#pragma once
#include <vector>
#include "Timer.h"
class Explosion;
class Bomb;
class MapObstacle;
class Player;
class ItemManager;
class BombManager;
enum firestate;
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
	void Set(Bomb &bomb);
	void Maintain();
	void CheckHitObject(MapObstacle *mapobstacle);
	void FireUp(const ItemManager &manageItem);	
	void CheckHitExplosion(Player *player);
	void Draw();
	//void SetFlag(firestate flag);
	ExplosionManager();
	~ExplosionManager(void);


std::vector<Explosion*> *vex;//vectorクラスのオブジェクト生成




};

