#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"

class Player;
class Enemy:
	public Charactor, virtual public IDrawable, virtual public IRegister
{
private:
	int graph[20];
	int muki;
	int animpat;
	int resetRoutine;
	int bombSet;
	int action[10];
	int actionloop;
public:
	Enemy(int x, int y);
	~Enemy(void);
	void Analyse();
	void Move(int g_lastTime);
	void Draw();
	int GetBombSet(void)const;
};

