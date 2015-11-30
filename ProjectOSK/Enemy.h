#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"

#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Player;
class EnemyAI;
class Timer;
class Enemy:
	public Charactor
{
protected:
	bool PutBomb() override;
public:
	void Update() override;
private:
	const int* image_left;
	const int* image_right;
	const int* image_up;
	const int* image_down;
	const int* image_death;
	int muki;
	int stop;
	int animpat;
	mutable int bombSet;
	int action[10];
	int hitNumSpeedUpItem;
	EnemyAI *const AI;
	int hasFinished;
	Timer* animationTime;
	int animationFrame;
public:
	Enemy(int x, int y);
	~Enemy();

	void Move()override;
	void Draw()override;
	void SetMv()override;
};

