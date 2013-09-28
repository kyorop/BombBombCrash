#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"
#include "EnemyAI.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

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
	int nextAction;
	int moveNow;
	EnemyAI AI;
public:
	Enemy(int x, int y);
	~Enemy(void);
	
	void Move(int g_lastTime);
	void Draw();
	int GetBombSet(void)const;
	int CheckAbleBombSet();
};

