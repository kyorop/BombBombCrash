#pragma once
#include "MapObject.h"
#include <list>

class Timer;
class Bomb;
class MapObstacle;
class Player;
class Charactor;
class BombManager;
class Item;
class Explosion:
	public MapObject
{
private:
	const int graph;
	const int upx,downx,upy,downy;
	Timer *time;
	int fuse;
	int explosion;
	//HACK: センターの廃止
	const int isCenter;
	std::list<Explosion*> nextFire;

public:
	Explosion(int center, int right,int left,int down,int up);
	~Explosion(void);

	void Set(int x, int y);
	//void CheckHitObject(MapObstacle *mapobstacle);
	//virtual int CheckHItCharactor(Charactor *charactor);//オーバーライド
	//void CheckHitBomb(Bomb *bomb);
	//void CheckHitItem(Item *item);
	int GetExplosion();
	void SetFuse(int flag);
	void SetExplosion(int flag);
	//void SetNext(Explosion *nextFire);
	//Explosion* GetNext();
};

