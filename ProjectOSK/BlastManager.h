#pragma once
#include "IDrawable.h"
#include <vector>

class ExplosionManager;
class BombManager;
class MapObstacle;
class Player;
class ItemManager;
class Charactor;
class Bomb;
class BlastManager:
	virtual public IDrawable
{
private:
	
	int nowBlastNum;
	
	
public:
	void FireUp(const Charactor &charactor)const;
	void Add(const Charactor &charactor);
	void Set(const BombManager &bombManager);
	void Maintain(const BombManager &bombManager);
	void CheckHitObject(MapObstacle *mapobstacle);
	void CheckHitCharactor(Charactor *charactor);
	void CheckHitBomb(BombManager *bombManager);
	void CheckHitItem(ItemManager *itemManager);
	void CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager);
	void Draw();
	BlastManager(void);
	~BlastManager(void);


	std::vector<ExplosionManager*> *vblast;
	
};

