#pragma once
#include "BombManager.h"

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

