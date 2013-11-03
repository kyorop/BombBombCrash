#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "DxLib.h"
#include <iostream>
#define BOMBEXISTTIME 3000
#define DHIT 5
#define KBHABA 16

//int Bomb::image_bomb[60];

//コンストラクタ
Bomb::Bomb()
	:fireLevel(1),
	animpat(0),
	image_bomb(Image::GetInstance()->GetBombImage())
{
	flag = 0;
	x = 0;
	y = 0;
	rx = x+32;
	dy =y+32;
	//LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, image_bomb, FALSE);
	Collision::GetInstance()->Register(this);
}

Bomb::~Bomb()
{
}

void Bomb::Set(int x, int y)
{
	if(flag == 0 )
	{
		//プレイヤーの重心のいるマス
		int xMasuNum = (x + x + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (y + y + 32) / 2 / 32;//上から何マス目か
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		this->rx = this->x+32;
		this->dy = this->y+32;
		flag = 1;
	}
}


void Bomb::CheckBombOverlap(const Bomb &bomb)
{
	if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
	{
		this->flag = 0;
	}
}


void Bomb::Maintain()
{	
	if(flag == 0)
		time.TurnReset();
	else
	{
		if(time.CountDown(BOMBEXISTTIME) == true)//三秒たったら
			flag = 0;
	}
}


void Bomb::SetFlag(int flag)
{
	this->flag = flag;
	if(flag == FALSE)
		this->time.TurnReset();
}


void Bomb::Draw()
{
	animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 3;
	if(flag == 1)
	{
		SetTransColor(255,255,255);
		DrawGraph(x, y, image_bomb[animpat], TRUE);
	}
}


void Bomb::Register()
{
	if(flag == 0)
		MapState::GetInstance()->SetBombState(x, y, 0);
	else
	{
		MapState::GetInstance()->SetBombState(x, y, 1);
		MapState::GetInstance()->SetBombState(x, y, fireLevel, 1);
	}
}

void Bomb::SetFireLevel(int level)
{
	fireLevel = level;
}
