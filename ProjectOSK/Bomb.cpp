#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "Sound.h"
#include "DxLib.h"
#include <iostream>
#define BOMBEXISTTIME 2500
#define DHIT 5
#define KBHABA 16


Bomb::Bomb()
	:fireLevel(1),
	animpat(0),
	image_bomb(Image::GetInstance()->GetBombImage()),
	soundOn(0)
{
	flag = 0;
	x = 0;
	y = 0;
	rx = x+32;
	dy =y+32;
	MapState::GetInstance()->Register(this);
	Collision::GetInstance()->Register(this);
	Sound::GetInstance()->Register(this);
}

Bomb::~Bomb()
{
}

void Bomb::Set(int x, int y)
{
	if(flag == 0 )
	{
		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (x + x + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (y + y + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
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
		if(time.CountDownFrame(BOMBEXISTTIME) == true)//�O�b��������
		{
			flag = 0;
			soundOn = 1;
		}
	}
}


void Bomb::SetFlag(int flag)
{
	this->flag = flag;
	if(flag == FALSE)
	{
		this->time.TurnReset();
		soundOn = 1;
	}
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


//void Bomb::Register()
//{
//	if(flag == 0)
//		MapState::GetInstance()->SetBombState(x, y, 0);
//	else
//	{
//		MapState::GetInstance()->SetBombState(x, y, 1);
//		MapState::GetInstance()->SetBombState(x, y, fireLevel, 1);
//	}
//}


void Bomb::SetFireLevel(int level)
{
	fireLevel = level;
}


int Bomb::EnableToPlaySound()const
{
	if(soundOn)
	{
		soundOn = 0;
		return 1;
	}
	else
		return 0;
}
