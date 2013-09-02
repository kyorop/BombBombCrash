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

void Bomb::BombSet(const Charactor &charactor,const Map &map)
{
	if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//���e�̂Ȃ�����z�������ꂽ��//z�����������̃v���C���[�̍��W�̎擾
	{
		this->explosion = 0;

		//�v���C���[�̏d�S�́A�}�b�v��ł�ID
		int x_center = (charactor.GetX() + charactor.GetX() + 32) / 2;
		int y_center = (charactor.GetY() + charactor.GetY() + 32) / 2;

		//����ID�̍��W����
		this->x = map.x[y_center/32][x_center/32];
		this->y = map.y[y_center/32][x_center/32];

		this->flag = 1;
	}
}

void Bomb::Draw()
{
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

	if(resetTime == true)
	{
		startTime = GetNowCount();
		resetTime = false;
	}

	if(GetNowCount() - startTime < time)//3�b�Ԃ̓X�^�[�g���Ԃ����Z�b�g���Ȃ�
	{
		return TRUE;		//���e��\��������
	}
	else
	{
		resetTime = true;//3�b��������X�^�[�g���Ԃ����Z�b�g����
		return FALSE;		//���e������
	}
}