#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "DxLib.h"
#include <iostream>
//#include <cstdio>
#define BOMBEXISTTIME 3000

//コンストラクタ
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
	//if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//爆弾のない時にzが押されたら//zを押した時のプレイヤーの座標の取得
	if(CheckHitKey(KEY_INPUT_Z) && this->flag == 0 )
	{
		
		//プレイヤーの重心のいるマス
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//上から何マス目か
		
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
		if(this->time.CountDown(BOMBEXISTTIME) == true)//三秒たったら
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

	if( this->flag == 1)//zが押されて、またその時から3秒以内なら、爆弾を表示し続ける
	{
		SetTransColor(255,255,255);
		DrawGraph(this->x, this->y, this->graph[0], TRUE);	
	}
	//else//爆発
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
