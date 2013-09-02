#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "DxLib.h"
#define DHIT 6

/*
void Explosion::Draw(const Map &map, const Bomb &bomb)
{
	//DrawGraph(this->x,this->y, this->graph, FALSE);

	this->x = bomb.x;
	this->y = bomb.y;

	//int x_center = (this->x + this->x + 32) / 2;
	//int y_center = (this->y + this->y + 32) / 2;

	if(bomb.flag == 1)
		this->flag = 1;

	if(bomb.flag == 0)
	{
		if(this->flag == 1)
			this->flag = 2;
	}
	if(this->flag == 2)
	{
		if(Timer(3000))
		{
			//DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32],this->graph,FALSE);//中心

			//DrawGraph(this->x+32*p-32*q, this->y+32*r-32*s,this->graph,FALSE);//中心
			DrawGraph(this->xHZ, this->yHZ,this->graph,FALSE);//中心
			//if(map.mapchip[y_center/32][x_center/32-1] == 0)DrawGraph(map.x[y_center/32][x_center/32]-32, map.y[y_center/32][x_center/32],	this->graph, TRUE);//左	
			//if(map.mapchip[y_center/32][x_center/32+1] == 0)DrawGraph(map.x[y_center/32][x_center/32]+32, map.y[y_center/32][x_center/32],this->graph, TRUE);//右
			//if(map.mapchip[y_center/32-1][x_center/32] == 0)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]-32,	this->graph, TRUE);//上	
			//if(map.mapchip[y_center/32+1][x_center/32] == 0)DrawGraph(map.x[y_center/32][x_center/32], map.y[y_center/32][x_center/32]+32,this->graph, TRUE);//下

			//if(map.mapchip[y_center/32][x_center/32-1] == 0)DrawGraph(this->x-32, this->y,	this->graph, TRUE);//左	
			//if(map.mapchip[y_center/32][x_center/32+1] == 0)DrawGraph(this->x+32, this->y,this->graph, TRUE);//右
			//if(map.mapchip[y_center/32-1][x_center/32] == 0)DrawGraph(this->x, this->y-32,	this->graph, TRUE);//上	
			//if(map.mapchip[y_center/32+1][x_center/32] == 0)DrawGraph(this->x, this->y+32,this->graph, TRUE);//下
		}
		else
			this->flag = 0;
	}
}
*/

//コンストラクタ
Explosion::Explosion(int upx,int downx,int upy,int downy):
	graph(LoadGraph("fire.bmp")),upx(upx),downx(downx),upy(upy),downy(downy)
{
}

//ボムが置かれて、それが爆発すると、火を存在させる
void Explosion::SetExplosion(const Bomb &bomb)//爆弾のあとExplosionManagerの中で一番初めに描く
{
	if(bomb.flag == 1)//ボムが置かれた
		this->flag = 1;

	else if(bomb.flag == 0 && this->flag == 1)//ボムが爆発した
	{
		this->flag = 2;
		this->x = bomb.x + 32*upx - 32*downx;//中心からの広がり
		this->y = bomb.y + 32*upy - 32*downy;
	}
}

//火が存在しているならば、座標を与える
void Explosion::SetZahyou(const Bomb &bomb)//中心座標
{
	this->x = bomb.x + 32*upx - 32*downx;//中心からの広がり
	this->y = bomb.y + 32*upy - 32*downy;
}

//プレイヤーとのあたり判定
int Explosion::CheckHItCharactor(Charactor *charactor)//ObjectのCheckHitをオーバーライド
{
	if(this->flag == 2)//火が存在しているとき
	{
		if(this->x+32-DHIT > charactor->GetX() && this->x+DHIT < charactor->GetRX() && this->y+DHIT < charactor->GetDY() && charactor->GetY() < this->y+32-DHIT)
		{
			charactor->SetCharactorState(FALSE);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

//壁とのあたり判定
void Explosion::CheckHitObject(MapObstacle *mapobstacle)
{
	int i = this->y / 32;
	int j = this->x / 32;

	if(this->flag == 2)
	{
		if(mapobstacle->GetID(i, j) == 1)//火が描かれる予定の場所の識別値がマップの壁なら、火を書かないようにする。
		{
			this->flag = 0;
		}
		else if(mapobstacle->GetFlag(i, j) == TRUE)//火が描かれる予定の場所の識別値が、壊れるブロックなら、そのブロックを壊して、火は描かない
		{
			mapobstacle->SetFlag(i, j, FALSE);//ブロックを消す
			//mapobstacle->SetID(i, j, 0);//床とみなす
			this->flag = 0;//火は消す
		}
	}
}

//火が存在していれば、描く
void Explosion::Draw(const Bomb &bomb)
{
	if(this->flag == 2)
	{
		DrawGraph(this->x, this->y,this->graph,FALSE);
	}
}

//デストラクタ
Explosion::~Explosion(void)
{
}

//呼ばれてから引数ミリ秒カウントする
bool Explosion::Timer(int time)
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

int Explosion::GetFlag()const
{
	return this->flag;
}

void Explosion::SetFlag(int flag)
{
	this->flag = flag;
}