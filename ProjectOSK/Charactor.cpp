#include "Charactor.h"

namespace BombBombCrash
{
	int Character::idGenerator;

	Character::Character(const ln::Vector2& position, int width, int height): 
	MapObject(position, width, height),
	preX(),
	preY(),
	id(idGenerator++)
	{
	}

	Character::~Character(void)
	{
		--idGenerator;
	}
}


