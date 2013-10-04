#pragma once
#include "BombManager.h"

class Enemy;
class Charactor;
class EnemyBombManager:
	public BombManager
{
public:
	void BombSet(const Enemy &myself);
	void AddBomb(const Charactor &myself);
	void Register(const Charactor &myself);
	EnemyBombManager(void);
	~EnemyBombManager(void);
};

