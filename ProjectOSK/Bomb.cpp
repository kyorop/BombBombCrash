#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include "Charactor.h"
#include "DxLib.h"
#include <iostream>
//#include <cstdio>
#define BOMBEXISTTIME 3000
#define DHIT 5
#define KBHABA 16

//コンストラクタ
Bomb::Bomb()
{
	this->count=0;
	this->explosion = 0;
	this->flag = 0;
	this->x = 0;
	this->y = 0;
	this->rx = this->x+32;
	this->dy = this->y+32;
	LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, this->graph, FALSE);
	this->fuse = 1;
}

void Bomb::CheckHit(Charactor *charactor)
{
	//□←
			if( (this->rx-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx) && (this->y+DHIT <= charactor->GetY() && charactor->GetY() < this->dy-DHIT) && this->flag == TRUE)charactor->SetX(this->x + 32);//途中
			if( (this->rx-DHIT <= charactor->GetX() && charactor->GetX() <= this->rx) && (this->y+DHIT <= charactor->GetDY() && charactor->GetDY() < this->dy-DHIT) && this->flag == TRUE)charactor->SetX(this->x + 32);//上いった
	
			////→□
			//if((this->x[uy][lx] <= charactor->GetX() && charactor->GetX() < this->x[uy][lx]+DHIT) && (this->y[uy][rx]+DHIT <= charactor->GetY() && charactor->GetY() < this->dy[uy][rx]-DHIT) && this->flag[uy][rx] == TRUE)charactor->SetX(this->x[uy][rx]- 32) ;//途中
			//if((this->x[dy][lx] <= charactor->GetX() && charactor->GetX() < this->x[dy][lx]+DHIT) && (this->y[dy][rx]+DHIT <=charactor->GetDY() && charactor->GetDY() < this->dy[dy][rx]-DHIT) && this->flag[dy][rx] == TRUE)charactor->SetX(this->x[dy][rx] - 32);//上いった
	
			//→□
			if((this->x <= charactor->GetRX() && charactor->GetRX() <= this->x+DHIT) && (this->y+DHIT <= charactor->GetY() && charactor->GetY() <= this->dy-DHIT) && this->flag == 1)charactor->SetX(this->x- 32);//途中
			if((this->x <= charactor->GetRX() && charactor->GetRX() <= this->x+DHIT) && (this->y+DHIT <=charactor->GetDY() && charactor->GetDY() <= this->dy-DHIT) && this->flag == 1)charactor->SetX(this->x - 32);//上いった

					
			//□
			//↑
			if( (this->dy-DHIT < charactor->GetY() && charactor->GetY() <= this->dy) && (this->x+DHIT <= charactor->GetX() && charactor->GetX() < this->rx-DHIT) && this->flag == TRUE)charactor->SetY(this->dy);//左行く
			if( (this->dy-DHIT < charactor->GetY() && charactor->GetY() <= this->dy) && (this->x+DHIT <= charactor->GetRX() && charactor->GetRX() < this->rx-DHIT) && this->flag == TRUE)charactor->SetY(this->dy);//右行く

			//↓
			//□
			if( (this->y< charactor->GetDY() && charactor->GetDY() <= this->y+DHIT) && (this->x+DHIT <= charactor->GetX() && charactor->GetX() < this->rx-DHIT) && this->flag == TRUE)charactor->SetY(this->y-32);//左行く
			if( (this->y < charactor->GetDY() && charactor->GetDY() <= this->y+DHIT) && (this->x+DHIT <= charactor->GetRX() && charactor->GetRX() < this->rx-DHIT) && this->flag== TRUE)charactor->SetY(this->y-32);//右行く

			//真左
			if( (this->y <= charactor->GetY() && charactor->GetY() < this->y+DHIT) && (this->rx-DHIT < charactor->GetX() && charactor->GetX() <= this->rx) && this->flag == TRUE)charactor->SetX(this->x + 32);
			if( (this->dy-DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy) && (this->rx-DHIT < charactor->GetX() && charactor->GetX() <= this->rx) && this->flag == TRUE )charactor->SetX(this->x + 32);

			//真右
			if( (this->y <= charactor->GetY() && charactor->GetY() < this->y+DHIT) && (this->x <= charactor->GetRX() && charactor->GetRX() < this->x+DHIT) && this->flag == TRUE)charactor->SetX(this->x- 32);
			if( (this->dy-DHIT <= charactor->GetDY() && charactor->GetDY() <= this->dy) && (this->x <= charactor->GetRX() && charactor->GetRX() < this->x+DHIT) && this->flag == TRUE)charactor->SetX(this->x - 32);

			//真上
			if( (this->x <= charactor->GetX() && charactor->GetX() < this->x+DHIT) && (this->dy-DHIT < charactor->GetY() && charactor->GetY() <= this->dy) && this->flag == TRUE)charactor->SetY(this->dy);
			if( (this->rx-DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx) && (this->dy-DHIT < charactor->GetY() && charactor->GetY() <= this->dy) && this->flag == TRUE)charactor->SetY(this->dy);

			//真下
			if( (this->x <= charactor->GetX() && charactor->GetX() < this->x+DHIT) && (this->y < charactor->GetDY() && charactor->GetDY() <= this->y+DHIT) && this->flag == TRUE)charactor->SetY(this->y - 32);
			if( (this->rx-DHIT <= charactor->GetRX() && charactor->GetRX() <= this->rx) && (this->y < charactor->GetDY() && charactor->GetDY() <= this->y+DHIT) && this->flag == TRUE)charactor->SetY(this->y - 32);

			//壁の左上角
			if( (this->x+DHIT < charactor->GetRX() && charactor->GetRX() < this->x+KBHABA) && (this->y+DHIT < charactor->GetDY() && charactor->GetDY() < this->y+KBHABA) && this->flag == 1)charactor->SetX(this->x-32+DHIT-charactor->GetMV());
			//壁の右上角
			if( (this->rx-KBHABA < charactor->GetX() && charactor->GetX() < this->rx-DHIT) && (this->y+DHIT < charactor->GetDY() && charactor->GetDY() < this->y+KBHABA) && this->flag == 1)charactor->SetX(this->rx-DHIT+charactor->GetMV());
			//壁の左下角
			if( (this->x+DHIT < charactor->GetRX() && charactor->GetRX() < this->x+KBHABA) && (this->dy-KBHABA < charactor->GetY() && charactor->GetY() < this->dy-DHIT) && this->flag == 1)charactor->SetX(this->x-32+DHIT-charactor->GetMV());
			//壁の右下角
			if( (this->rx-KBHABA < charactor->GetX() && charactor->GetX() < this->rx-DHIT) && (this->dy-KBHABA < charactor->GetY() && charactor->GetY() < this->dy-DHIT) && this->flag == 1)charactor->SetX(this->rx-DHIT+charactor->GetMV());
	
}

void Bomb::BombSet(int x, int y)
{
	//if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//爆弾のない時にzが押されたら//zを押した時のプレイヤーの座標の取得
	if(flag == 0 )
	{
		//プレイヤーの重心のいるマス
		int xMasuNum = (x + x + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (y + y + 32) / 2 / 32;//上から何マス目か
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		rx = this->x+32;
		dy = this->y+32;
		flag = 1;

		//if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
		//	this->flag = 0;
	}
}

void Bomb::CheckBombOverlap(const Bomb &bomb)
{
	if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
	{
		flag = 0;
		explosion = 0;
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

int Bomb::GetFuse(void)const
{
	return this->fuse;
}


void Bomb::SetFuse(int fuse)
{
	this->fuse = fuse;
}


int Bomb::GetExplosion(void)const
{
	return explosion;
}


void Bomb::SetExplosion(int explosion)
{
	this->explosion = explosion;
}
