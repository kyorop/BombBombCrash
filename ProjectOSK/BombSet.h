#pragma once
#include "IDrawable.h"

class Bomb;
class ExplosionManager;
class BombSet
	:public IDrawable
{
private:
	Bomb *const bomb;
	ExplosionManager *const explosion;
private:
	void Register();
public:
	BombSet(Bomb *bomb);
	~BombSet(void);
	void Set(int x, int y);
	void Update(void);
	void Draw(void);
};

