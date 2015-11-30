#include "Charactor.h"
#include "MapState.h"

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

void Character::Register()
{
	MapState::GetInstance()->SetCharactorState(this->preX, this->preY, 0);
	if(this->flag == 1)
		MapState::GetInstance()->SetCharactorState(this->x, this->y, 1);
	else if(this->flag == 0)
		MapState::GetInstance()->SetCharactorState(this->x, this->y, 0);
	this->preX = this->x;
	this->preY = this->y;
}