#pragma once
#include "Timer.h"
#include <vector>

class ExplosionManager;
class BombManager;
class MapObstacle;
class Player;
class ItemManager;
class BlastManager
{
private:
	std::vector<ExplosionManager*> *vblast;
	int nowBlastNum;
	Timer time;
	
public:
	void Add(const ItemManager &manageItem);
	void Set(const BombManager &bombManager);
	void CheckHitObject(MapObstacle *mapobstacle);
	void CheckHitExplosion(Player *player);
	void Draw();
	BlastManager(void);
	~BlastManager(void);
};

