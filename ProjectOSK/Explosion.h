#pragma once
#include "Object.h"
#include "Timer.h"

class Bomb;
class MapObstacle;
class Player;
class Charactor;
class BombManager;
class Item;
class Explosion:
	public Object
{
private:
	const int graph;
	const int upx,downx,upy,downy;
	Timer time;
	int fuse;
	int explosion;

public:
	void Set(const Bomb &bomb);
	void CheckHitObject(MapObstacle *mapobstacle);
	virtual int CheckHItCharactor(Charactor *charactor);//オーバーライド
	void CheckHitBomb(Bomb *bomb);
	void CheckHitItem(Item *item);
	void Draw();
	Explosion(int upx,int downx,int upy,int downy);
	~Explosion(void);

public:
	int GetExplosion();
	void SetFuse(int flag);
	void SetExplosion(int flag);
};

