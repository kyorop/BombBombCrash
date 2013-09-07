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
}

void Bomb::BombSet(const Charactor &charactor)
{
	//if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//���e�̂Ȃ�����z�������ꂽ��//z�����������̃v���C���[�̍��W�̎擾
	if(key.CheckOnePushKey(KEY_INPUT_Z) && this->flag == 0 )
	{
		this->explosion = 0;

		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		this->flag = 1;
	}
}

void Bomb::MaintainBomb()
{	
	/*
	if(this->flag == 1)
	{
		if(this->time.CountDown(BOMBEXISTTIME) == false)
			this->flag = 1;
		else
			this->flag = 0;	
	}
	*/
	if(this->flag == 1)
	{
		if(key.CheckOnePushKey(KEY_INPUT_SPACE) == TRUE)
			this->flag = FALSE;
		else
			this->flag = TRUE;
	}
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
	else//����
	{
		this->flag = 0;
		this->explosion = 1;
	}
}

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