#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "DxLib.h"
#include <iostream>


//コンストラクタ定義
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

int Bomb::Timer(int time)//この関数が呼び出されてから、規定時間たったら知らせる	
{
	static bool resetTime = true;
	static int startTime;

	if(resetTime == true)
	{
		startTime = GetNowCount();
		resetTime = false;
	}

	if(GetNowCount() - startTime < time)//3秒間はスタート時間をリセットしない
	{
		return TRUE;		//爆弾を表示させる
	}
	else
	{
		resetTime = true;//3秒たったらスタート時間をリセットする
		return FALSE;		//爆弾を消す
	}
}

void Bomb::BombSet(const Player &player,const Map &map)
{
	if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//爆弾のない時にzが押されたら//zを押した時のプレイヤーの座標の取得
	{
		this->x_center = (player.Get(0)+player.Get(0)+32) / 2;
		this->y_center = (player.Get(1)+player.Get(1)+32) / 2;

		this->x = map.x[y_center/32][x_center/32];
		this->y = map.y[y_center/32][x_center/32];

		//this->x = player.Get(0);
		//this->y = player.Get(1);
		//this->x_center = (this->x+this->x+32) / 2;//中心座標の取得	
		//this->y_center = (this->y+this->y+32) / 2;
		this->flag = 1;
	}
	/*
	if( this->flag == 1)//zが押されて、またその時から3秒以内なら、爆弾を表示し続ける
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
	if( this->flag == 1)//zが押されて、またその時から3秒以内なら、爆弾を表示し続ける
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
//	if(this->flag == 1)//爆弾がセットされたら爆発の準備
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
//			DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32],		this->graph_explosion,FALSE);//中心
//			if(map.mapchip[y_center/32][x_center/32-1] != 1)DrawGraph(map.x[y_center/32][x_center/32]-32, map.y[y_center/32][x_center/32],	this->graph_explosion, TRUE);//左	
//			if(map.mapchip[y_center/32][x_center/32+1] != 1)DrawGraph(map.x[y_center/32][x_center/32]+32, map.y[y_center/32][x_center/32],	this->graph_explosion, TRUE);//右
//			if(map.mapchip[y_center/32-1][x_center/32] != 1)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]-32,	this->graph_explosion, TRUE);//上	
//			if(map.mapchip[y_center/32+1][x_center/32] != 1)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]+32,	this->graph_explosion, TRUE);//下
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