#pragma once
#include "Bomb.h"

class Enemy;
class EnemyBomb:
	public Bomb
{
public:
	void BombSet(const Charactor &charactor);
	EnemyBomb(void);
	~EnemyBomb(void);
};

