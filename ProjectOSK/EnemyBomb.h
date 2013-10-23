#pragma once
#include "Bomb.h"

class Enemy;
class EnemyBomb:
	public Bomb
{
public:
	void BombSet(int x, int y);

	EnemyBomb(void);
	~EnemyBomb(void);
};

