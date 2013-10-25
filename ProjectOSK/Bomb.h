#pragma once
#include "MapObject.h"
#include "Key.h"
#include "Timer.h"

class Player;
class Map;
class Charactor;
class Bomb:
	public MapObject
{
	friend class Explosion;
protected:
	int count;
	Key key;
	Timer time;
public:
	Bomb();
	virtual ~Bomb();

	//void CheckHit(Charactor *charactor);
	virtual void BombSet(int x, int y) = 0;
	void MaintainBomb();
	//int CheckBombExplosion();
	void CheckBombOverlap(const Bomb & bomb);
	virtual void SetFlag(int flag);
public:
	int GetFuse(void)const;
	void SetFuse(int fuse);
	int GetExplosion(void)const;
	void SetExplosion(int explosion);
};

