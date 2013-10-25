#pragma once
#include "MapObject.h"

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

public:
	Explosion(int upx,int downx,int upy,int downy);
	~Explosion(void);

	void Set(int x, int y);
	//void CheckHitObject(MapObstacle *mapobstacle);
	//virtual int CheckHItCharactor(Charactor *charactor);//�I�[�o�[���C�h
	//void CheckHitBomb(Bomb *bomb);
	//void CheckHitItem(Item *item);
	int GetExplosion();
	void SetFuse(int flag);
	void SetExplosion(int flag);
};

