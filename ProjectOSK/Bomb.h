#pragma once
#include "MapObject.h"
#include "IColleague.h"
#include "Key.h"
#include "Timer.h"

class Player;
class Map;
class Charactor;
class Bomb
	:public MapObject
{
	friend class Explosion;
protected:
	int count;
	Key key;
	Timer time;
	int *const image_bomb;
public:
	Bomb();
	virtual ~Bomb();
	virtual void BombSet(int x, int y) = 0;
	void MaintainBomb();
	void CheckBombOverlap(const Bomb & bomb);
	virtual void SetFlag(int flag);
	void Draw();
public:
	int GetFuse(void)const;
	void SetFuse(int fuse);
	int GetExplosion(void)const;
	void SetExplosion(int explosion);
};

