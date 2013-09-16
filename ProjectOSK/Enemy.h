#pragma once
#include "Charactor.h"
#include "IDrawable.h"

class Player;
class Enemy:
	public Charactor, virtual public IDrawable
{
private:
	int graph[20];
	int muki;
	int animpat;
	int resetRoutine;
	int bombSet;
public:
	Enemy(int x, int y);
	~Enemy(void);
	void Analyse();
	void Move(int g_lastTime);
	void Draw();
	int GetBombSet(void)const;
};

