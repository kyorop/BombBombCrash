#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "DxLib.h"
#include <iostream>


//コンストラクタ
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
	if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//爆弾のない時にzが押されたら//zを押した時のプレイヤーの座標の取得
	{
		this->explosion = 0;

		//プレイヤーの重心の、マップ上でのID
		int x_center = (charactor.GetX() + charactor.GetX() + 32) / 2;
		int y_center = (charactor.GetY() + charactor.GetY() + 32) / 2;

		//そのIDの座標を代入
		this->x = map.x[y_center/32][x_center/32];
		this->y = map.y[y_center/32][x_center/32];

		this->flag = 1;
	}
}

void Bomb::Draw()
{
	if( this->flag == 1)//zが押されて、またその時から3秒以内なら、爆弾を表示し続ける
	{
		if(Timer(3000))
		{
			SetTransColor(255,255,255);
			DrawGraph(this->x, this->y, this->graph[0], TRUE);	
		}
		else//爆発
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