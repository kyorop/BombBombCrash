#pragma once
#include "Object.h"
#include "Timer.h"

class Bomb;
class MapObstacle;
class Player;
class Charactor;
class BombManager;
enum firestate;
class Explosion:
	public Object
{
private:
	const int graph;
	const int upx,downx,upy,downy;
	Timer time;
	firestate flag;

public:
	void SetExplosion(Bomb &bomb);
	void CheckHitObject(MapObstacle *mapobstacle);
	virtual int CheckHItCharactor(Charactor *charactor);//オーバーライド
	void Draw();
	Explosion(int upx,int downx,int upy,int downy);
	~Explosion(void);

public:
	firestate GetFlag()const;
	void SetFlag(firestate flag);
};

