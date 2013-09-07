#pragma once

#include <vector>

class ExplosionManager;
class BombManager;
class MapObstacle;
class Player;
class ItemManager;
class Charactor;
class Bomb;
class BlastManager
{
private:
	
	int nowBlastNum;
	
	
public:
	void FireUp(const ItemManager &itemManager);
	void Add(const ItemManager &manageItem);
	void Set(const BombManager &bombManager);
	void Maintain();
	void CheckHitObject(MapObstacle *mapobstacle);
	void CheckHitCharactor(Charactor *charactor);
	void CheckHitBomb(BombManager *bombManager);
	void Draw();
	BlastManager(void);
	~BlastManager(void);


	std::vector<ExplosionManager*> *vblast;
};

