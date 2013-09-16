#pragma once
#include "Bomb.h"

class Charactor;
class PlayerBomb:
	public Bomb
{
public:
	void BombSet(const Charactor &charactor);
	PlayerBomb(void);
	~PlayerBomb(void);
};

