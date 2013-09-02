#include "Charactor.h"
#include "Map.h"

Charactor::Charactor(void)
{
	x = 0;
	this->rx = 0;
	y = 0;
	this->dy = 0;
	this->flag = 0;
}

int Charactor::GetX()const
{
	return this->x;
}

int Charactor::GetY()const
{
	return this->y;
}

int Charactor::GetRX()const
{
	return this->rx;
}

int Charactor::GetDY()const
{
	return this->dy;
}

void Charactor::SetX(int x)
{
	this->x = x;
	this->rx = x + 32;
}

void Charactor::SetY(int y)
{
	this->y = y;
	this->dy = y + 32;
}

void Charactor::SetCharactorState(int flag)
{
	this->flag = flag;
}

Charactor::~Charactor(void)
{
}
