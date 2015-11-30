#pragma once
#include "MapObject.h"
#include "Timer.h"


class Bomb;

class Explosion:public MapObject
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


class ExplosionManager
{
private:
	int nowFireLevel;
	int fuse;
	int explosion;
	Timer retainFire;
	Timer beforeExplosion;
	static const int displayingTime = 200;
	const int image_fire;
	std::vector<Explosion*> vex;

public:
	int GetX(int i)const;
	int GetRX(int i)const;
	int GetY(int i)const;
	int GetDY(int i)const;
	int GetFlag(int i)const;
	void SetFlag(int i, int flag);
	int GetSize()const;
	void FireUp();
	void Update(const Bomb &bomb);
	void Maintain();
	void Draw();
	ExplosionManager();
	~ExplosionManager(void);


	void SetFuse(int flag);
	void Register(void);
	int GetExplosion(void);
	int Firepower(void);
};
