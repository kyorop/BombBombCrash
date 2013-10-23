#pragma once
#include "Bomb.h"

class Charactor;
class PlayerBomb:
	public Bomb
{
public:
	void BombSet(int x, int y);
	PlayerBomb(void);
	~PlayerBomb(void);
};

