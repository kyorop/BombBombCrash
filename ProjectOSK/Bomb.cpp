#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "DxLib.h"
#include <iostream>
//#include <cstdio>
#define BOMBEXISTTIME 3000

//�R���X�g���N�^
Bomb::Bomb()
{
	this->count=0;
	this->explosion = 0;
	this->flag = 0;
	this->x = 0;
	this->y = 0;
	LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, this->graph, FALSE);
	this->fuse = 1;
}

void Bomb::BombSet(const Charactor &charactor)
{
	//if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//���e�̂Ȃ�����z�������ꂽ��//z�����������̃v���C���[�̍��W�̎擾
	if(CheckHitKey(KEY_INPUT_Z) && this->flag == 0 )
	{
		
		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		this->flag = 1;

		//if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
		//	this->flag = 0;
	}
}

void Bomb::CheckBombOverlap(const Bomb &bomb)
{
	if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
	{
		this->flag = 0;
		this->explosion = 0;
		//this->time.TurnReset();
	}
}

void Bomb::MaintainBomb()
{	
	if(this->flag == 0)
	{
		time.TurnReset();
		this->explosion = 0;
	}
	else
	{
		if(this->time.CountDown(BOMBEXISTTIME) == true)//�O�b��������
		{
			this->explosion = 1;
			this->flag = 0;
		}
	}
}
//void Bomb::MaintainBomb()
//{	
//	if(this->flag == TRUE)
//	{
//		//if(this->time.CountDown(BOMBEXISTTIME) == false)
//		//	this->flag = TRUE;
//		//else
//		if(this->time.CountDown(BOMBEXISTTIME) == true)
//			this->flag = FALSE;	
//	}
//	/*
//	if(this->flag == 1)
//	{
//		if(key.CheckOnePushKey(KEY_INPUT_SPACE) == TRUE)
//			this->flag = FALSE;
//		else
//			this->flag = TRUE;
//	}
//	*/
//}

int Bomb::CheckBombExplosion()
{
	if(this->explosion == 1)
		return TRUE;
	else
		return FALSE;
}

Bomb::~Bomb()
{
}

void Bomb::Draw()
{

	if(key.CheckOnePushKey(KEY_INPUT_A))
	{
		this->flag = 0;
	}

	if( this->flag == 1)//z��������āA�܂����̎�����3�b�ȓ��Ȃ�A���e��\����������
	{
		SetTransColor(255,255,255);
		DrawGraph(this->x, this->y, this->graph[0], TRUE);	
	}
	//else//����
	//{
	//	this->flag = 0;
	//	this->explosion = 1;
	//}
}

void Bomb::SetFlag(int flag)
{
	this->flag = flag;
	if(flag == FALSE)
	{
		this->time.TurnReset();
	}
}

int Bomb::GetFuse(void)
{
	return this->fuse;
}


void Bomb::SetFuse(int fuse)
{
	this->fuse = fuse;
}


int Bomb::GetExplosion(void)
{
	return this->explosion;
}


void Bomb::SetExplosion(int explosion)
{
	this->explosion = explosion;
}
