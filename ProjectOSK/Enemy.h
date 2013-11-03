#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"

#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Player;
class EnemyAI;
class Enemy:
	public Charactor
{
private:
	const int* image_left;
	const int* image_right;
	const int* image_up;
	const int* image_down;
	int muki;
	int stop;
	int animpat;
	int bombSet;
	int action[10];
	EnemyAI *const AI;
public:
	Enemy(int x, int y);
	~Enemy();

	void Move()override;
	void Draw()override;
	int EnableBomb(void)const override;
};

