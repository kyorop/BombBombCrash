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
	std::vector<Explosion*> *vex;//vectorクラスのオブジェクト生成
	int addFireNum;
	int nowFireLevel;
	firestate flag;
	Timer time;
public:
	//void SetExplosion(const BombManager &bombManager);
	void Set(Bomb &bomb);
	void Maintain();
	void CheckHitObject(MapObstacle *mapobstacle);
	void Add(const ItemManager &manageItem);	
	void CheckHitExplosion(Player *player);
	void Draw();
	void SetFlag(firestate flag);
	firestate GetFlag()const;
	ExplosionManager();
	~ExplosionManager(void);
};

