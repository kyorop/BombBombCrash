#pragma once
#include "Object.h"
#include "Key.h"
#include "Timer.h"
#define BOMBDEVIDENUMBER 60

class Player;
class Map;
class Charactor;
class Bomb:
	public Object
{
	friend class Explosion;
protected:
	int rx;
	int dy;
	int count;
	int graph[BOMBDEVIDENUMBER];
	int explosion;
	Key key;
	Timer time;
public:
	
	Bomb();
	virtual ~Bomb();
	void CheckHit(Charactor *charactor);
	virtual void BombSet(int x, int y) = 0;
	void Draw();
	void MaintainBomb();
	int CheckBombExplosion();
	void CheckBombOverlap(const Bomb & bomb);
	virtual void SetFlag(int flag);
private:
	int fuse;
public:
	int GetFuse(void)const;
	void SetFuse(int fuse);
	int GetExplosion(void)const;
	void SetExplosion(int explosion);
};

