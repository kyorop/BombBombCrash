#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "DxLib.h"
#include <iostream>


//�R���X�g���N�^
Bomb::Bomb()
{
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
	/*
	if(this->flag == 1)
	{
		if(Timer(3000))
			this->flag = 1;
		else
			this->flag = 0;
	}
	*/
}

void Bomb::MaintainBomb(int time)
{
	static int startTime;
	static int reset = 1;
	if(this->flag == 1)
	{
		if(reset == 1)
		{
			startTime = GetNowCount();
			reset = 0;
		}

		if(GetNowCount() - startTime < time)
			this->flag = 1;
		else
		{
			this->flag = 0;
			reset = 1;
		}
	}
}

void Bomb::Draw()
{

	if(key.CheckOnePushKey(KEY_INPUT_A))
	{
		this->flag = 0;
	}
	/*
	if( this->flag == 1)//z��������āA�܂����̎�����3�b�ȓ��Ȃ�A���e��\����������
	{
		if(Timer(3000))
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
	*/
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

int Bomb::Timer(int time)//���̊֐����Ăяo����Ă���A�K�莞�Ԃ�������m�点��	
{
	static bool resetTime = true;
	static int startTime;
	static int count;
	if(resetTime == true)
	{
		startTime = GetNowCount();
		resetTime = false;
		count = 0;
	}
	
	if(GetNowCount() - startTime < time && resetTime == false)//3�b�Ԃ̓X�^�[�g���Ԃ����Z�b�g���Ȃ�
	{
		return TRUE;		//���e��\��������
	}
	else
	{
		resetTime = true;//3�b��������X�^�[�g���Ԃ����Z�b�g����
		return FALSE;		//���e������
	}
	

	//if(resetTime == false)
	//{
	//	++count;
	//		if(count > 180)
	//		{
	//			resetTime = true;
	//			return false;
	//		}
	//		else
	//			return true;
	//}
	//else
	//	return false;


}