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
public:
	BombSet();
	~BombSet(void);
	void Set(int x, int y);
	void Update(void);
	void Draw(void);
	void UpFireLevel(void);
	int GetBombX()const;
	int GetBombY()const;
	int GetFlag()const;
	void SetFlag(int flag);
};

