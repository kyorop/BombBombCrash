#pragma once
#include "MapObject.h"
#include "Key.h"
#include "Timer.h"
#define BOMBDEVIDENUMBER 60

class Player;
class Map;
class Charactor;
class Bomb:
	public MapObject
{
	friend class Explosion;
protected:
	int count;
	int graph[BOMBDEVIDENUMBER];
	int explosion;
	Key key;
	Timer time;
public:
	Bomb();
	virtual ~Bomb();

	void CheckHit(Charactor *charactor);
	virtual void BombSet(const Charactor &charactor) = 0;
	void Draw();
	void MaintainBomb();
	int CheckBombExplosion();
	void CheckBombOverlap(const Bomb & bomb);
	virtual void SetFlag(int flag);
private:
	int fuse;
public:
	int GetFuse(void);
	void SetFuse(int fuse);
	int GetExplosion(void);
	void SetExplosion(int explosion);
};

