#pragma once
#include "BombManager.h"

class Enemy;
class EnemyBombManager:
	public BombManager
{
public:
	void BombSet(const Enemy &enemy);
	void AddBomb(const Charactor &charactor);
	EnemyBombManager(void);
	~EnemyBombManager(void);
};

