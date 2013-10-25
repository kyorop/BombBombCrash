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

	void CheckHit(Charactor *charactor);
	virtual void BombSet(const Charactor &charactor) = 0;
	void MaintainBomb();
	int CheckBombExplosion();
	void CheckBombOverlap(const Bomb & bomb);
	virtual void SetFlag(int flag);
public:
	int GetFuse(void);
	void SetFuse(int fuse);
	int GetExplosion(void);
	void SetExplosion(int explosion);
};

