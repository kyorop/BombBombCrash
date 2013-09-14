#pragma once
#include "Charactor.h"
#include "IDrawable.h"

class Player;
class Enemy :
	public Charactor, virtual public IDrawable
{
private:
	int graph[20];
	int muki;
	int animpat;
	int resetRoutine;
public:
	Enemy(int x, int y);
	~Enemy(void);
	void Analyse();
	void Move(int g_lastTime, const Player &player);
	void Draw();
};

