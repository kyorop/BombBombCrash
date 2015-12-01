#include "Charactor.h"
#include "MapState.h"
#include "Player.h"

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