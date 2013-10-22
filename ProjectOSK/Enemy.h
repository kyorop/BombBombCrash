#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"

#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Player;
class EnemyAI;
class Enemy:
	public Charactor, virtual public IDrawable
{
private:
	//int nowStop;
	int graph[20];
	int muki;
	int stop;
	int animpat;
	//int resetRoutine;
	int bombSet;
	int action[10];
public:
	Enemy(int x, int y);
	~Enemy(void);
	EnemyAI *const AI;
	void Order();
	void Move(int g_lastTime);
	void Draw();
	int GetBombSet(void)const;
};

