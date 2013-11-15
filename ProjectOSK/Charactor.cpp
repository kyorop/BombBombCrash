#include "Charactor.h"
#include "Map.h"
#include "MapState.h"
#include "DxLib.h"

int Charactor::idGenerator;

Charactor::Charactor(void)
	:preX(),
	preY(),
	mv(1),
	bombNum(1),
	fireLevel(1),
	id(idGenerator)
{
	++idGenerator;
}

Charactor::~Charactor(void)
{
}


int Charactor::GetMV(void)const
{
	return mv;
}


int Charactor::GetBombNum(void)const
{
	return bombNum;
}


int Charactor::GetFireLevel(void)const
{
	return fireLevel;
}


void Charactor::AddBombNum(void)
{
	++bombNum;
}


void Charactor::AddFireLevel(void)
{
	++fireLevel;
}


void Charactor::AddMV(void)
{
	++mv;
}


void Charactor::Register()
{
	MapState::GetInstance()->SetCharactorState(this->preX, this->preY, 0);
	if(this->flag == 1)
		MapState::GetInstance()->SetCharactorState(this->x, this->y, 1);
	else if(this->flag == 0)
		MapState::GetInstance()->SetCharactorState(this->x, this->y, 0);
	this->preX = this->x;
	this->preY = this->y;
}