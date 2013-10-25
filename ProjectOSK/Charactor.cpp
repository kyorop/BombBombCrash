#include "Charactor.h"
#include "Map.h"
#include "MapState.h"
#include "DxLib.h"

Charactor::Charactor(void)
	:preX(),
	preY(),
	mv(3),
	bombNum(1),
	fireLevel(1)
{
}

Charactor::~Charactor(void)
{
}

void Charactor::SetCharactorState(int flag)
{
	this->flag = flag;
}



int Charactor::GetMV(void)const
{
	return this->mv;
}

int Charactor::GetBombNum(void)
{
	if(CheckHitKey(KEY_INPUT_SPACE) == 1)
		++bombNum;

	return this->bombNum;
}


int Charactor::GetFireLevel(void)const
{
	return this->fireLevel;
}


void Charactor::AddBombNum(void)
{
	++this->bombNum;
}


void Charactor::AddFireLevel(void)
{
	++this->fireLevel;
}


void Charactor::AddMV(void)
{
	++this->mv;
}

int Charactor::GetBombSet()const
{
	return 0;
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