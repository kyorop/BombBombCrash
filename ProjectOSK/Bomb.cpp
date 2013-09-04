#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "DxLib.h"
#include <iostream>


//�R���X�g���N�^��`
Bomb::Bomb()
{
	this->flag = 0;
	this->x = 0;
	this->y = 0;
	this->x_center = (this->x+this->x+32) / 2;
	this->y_center = (this->y+this->y+32) / 2;
	LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, this->graph, FALSE);
	//graph_explosion = LoadGraph("fire.bmp");
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

void Bomb::BombSet(const Player &player,const Map &map)
{
	if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//���e�̂Ȃ�����z�������ꂽ��//z�����������̃v���C���[�̍��W�̎擾
	{
		this->x_center = (player.Get(0)+player.Get(0)+32) / 2;
		this->y_center = (player.Get(1)+player.Get(1)+32) / 2;

		this->x = map.x[y_center/32][x_center/32];
		this->y = map.y[y_center/32][x_center/32];

		//this->x = player.Get(0);
		//this->y = player.Get(1);
		//this->x_center = (this->x+this->x+32) / 2;//���S���W�̎擾	
		//this->y_center = (this->y+this->y+32) / 2;
		this->flag = 1;
	}
	/*
	if( this->flag == 1)//z��������āA�܂����̎�����3�b�ȓ��Ȃ�A���e��\����������
	{
		if(BombTimer(3000))
		{
			SetTransColor(255,255,255);
			//DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32], this->graph[0], TRUE);	
			DrawGraph(this->x, this->y, this->graph[0], TRUE);	
		}
		else
		{
			this->flag = 0;
		}
	}
	*/
	//SetExplosion(map);
}

void Bomb::Draw()
{
	if( this->flag == 1)//z��������āA�܂����̎�����3�b�ȓ��Ȃ�A���e��\����������
	{
		if(Timer(3000))
		{
			SetTransColor(255,255,255);
			//DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32], this->graph[0], TRUE);	
			DrawGraph(this->x, this->y, this->graph[0], TRUE);	
		}
		else
		{
			this->flag = 0;
		}
	}
}

//void Bomb::SetExplosion(const Map &map)
//{
//	/*
//	static bool ready = false;
//
//	if(this->flag == 1)//���e���Z�b�g���ꂽ�甚���̏���
//	{
//		ready = true;
//	}
//	if(ready == true && this->flag == 0)
//	{
//		if(Timer(2000))
//		{
//			DrawGraph(this->x, this->y, this->graph_explosion, FALSE);
//		}
//		else
//		{
//			ready = false;
//		}
//	}
//	*/
//	static int fireon;
//
//	if(this->flag == 1)
//		fireon = 1;
//
//	if(this->flag == 0)
//	{
//		if(fireon == 1)
//			fireon = 2;
//	}
//	if(fireon == 2)
//	{
//		if(ExplosionTimer(3000))
//		{
//			DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32],		this->graph_explosion,FALSE);//���S
//			if(map.mapchip[y_center/32][x_center/32-1] != 1)DrawGraph(map.x[y_center/32][x_center/32]-32, map.y[y_center/32][x_center/32],	this->graph_explosion, TRUE);//��	
//			if(map.mapchip[y_center/32][x_center/32+1] != 1)DrawGraph(map.x[y_center/32][x_center/32]+32, map.y[y_center/32][x_center/32],	this->graph_explosion, TRUE);//�E
//			if(map.mapchip[y_center/32-1][x_center/32] != 1)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]-32,	this->graph_explosion, TRUE);//��	
//			if(map.mapchip[y_center/32+1][x_center/32] != 1)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]+32,	this->graph_explosion, TRUE);//��
//		}
//		else
//			fireon = 0;
//	}
//
//
//}*/

Bomb::~Bomb()
{

}