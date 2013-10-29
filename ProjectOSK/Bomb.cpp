#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "DxLib.h"
#include <iostream>
#define BOMBEXISTTIME 3000
#define DHIT 5
#define KBHABA 16

//コンストラクタ
Bomb::Bomb()
{
	this->count=0;
	this->flag = 0;
	this->x = 0;
	this->y = 0;
	this->rx = this->x+32;
	this->dy = this->y+32;
}

Bomb::~Bomb()
{
}

void Bomb::CheckBombOverlap(const Bomb &bomb)
{
	if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
	{
		this->flag = 0;
	}
}


void Bomb::MaintainBomb()
{	
	if(this->flag == 0)
	{
		time.TurnReset();
	}
	else
	{
		if(this->time.CountDown(BOMBEXISTTIME) == true)//三秒たったら
		{
			this->flag = 0;
		}
	}
}


void Bomb::SetFlag(int flag)
{
	this->flag = flag;
	if(flag == FALSE)
	{
		this->time.TurnReset();
	}
}
