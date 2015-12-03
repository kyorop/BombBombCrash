#include "Charactor.h"

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