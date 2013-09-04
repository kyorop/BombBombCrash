#pragma once
#include "Object.h"

class Bomb;
class MapObstacle;
class Player;

class Explosion:
	public Object
{
private:
	bool Timer(int time);

private:
	const int graph;
	const int upx,downx,upy,downy;

public:
	void SetExplosion(const Bomb &bomb);
	void CheckHitObject(MapObstacle *mapobstacle);
	void CheckHItCharactor(Player *player);//�I�[�o�[���C�h
	void SetZahyou(const Bomb &bomb);
	void Draw(const Bomb &bomb);
	Explosion(int upx,int downx,int upy,int downy);
	~Explosion(void);

public:
	int GetFlag()const;
	void SetFlag(int flag);
};

