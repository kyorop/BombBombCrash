#include "Charactor.h"

namespace BombBombCrash
{
	int Character::idGenerator;

	Character::Character(void)
		:preX(),
		 preY(),
		 id(idGenerator)
	{
		++idGenerator;
	}

	Character::~Character(void)
	{
		--idGenerator;
	}
}


