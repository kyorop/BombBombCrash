#pragma once
#include "MapObject.h"
#include <list>


class Explosion:
	public MapObject
{
private:
	const int upx,downx,upy,downy;
	int fuse;
	int explosion;

public:
	Explosion(int right,int left,int down,int up);
	~Explosion(void);

	void Set(int x, int y);
	int GetExplosion();
	void SetFuse(int flag);
	void SetExplosion(int flag);
};

