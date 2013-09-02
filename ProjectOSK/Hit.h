#pragma once
#include "Player.h"
class Hit
{
	friend class Player;

private:
	int x;
	int y;
	int width;
	int height;

public:

	void CheckHit(Player *player);
	Hit(void);
	~Hit(void);
};

