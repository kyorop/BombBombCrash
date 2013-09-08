#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "BombManager.h"
#include "Item.h"
#include "DxLib.h"
#define DHIT 6

//コンストラクタ
Explosion::Explosion(int upx,int downx,int upy,int downy):
	graph( LoadGraph("fire.bmp") ), upx(upx), downx(downx), upy(upy), downy(downy)
{
	this->fuse = 0;
	this->explosion = 0;
}

//ボムが置かれて、それが爆発すると、火を存在させる
void Explosion::Set(const Bomb &bomb)//爆弾のあとExplosionManagerの中で一番初めに描く
{
	this->x = bomb.GetX() + 32*upx - 32*downx;//中心からの広がり
	this->y = bomb.GetY() + 32*upy - 32*downy;
}

//プレイヤーとのあたり判定
int Explosion::CheckHItCharactor(Charactor *charactor)//ObjectのCheckHitをオーバーライド
{
	if(this->explosion == TRUE)//火が存在しているとき
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

	if(this->explosion == TRUE)
	{
		if(mapobstacle->GetID(i, j) == 1)//火が描かれる予定の場所の識別値がマップの壁なら、火を書かないようにする。
		{
			this->explosion = FALSE;
		}
		else if(mapobstacle->GetFlag(i, j) == TRUE)//火が描かれる予定の場所の識別値が、壊れるブロックなら、そのブロックを壊して、火は描かない
		{
			mapobstacle->SetFlag(i, j, FALSE);//ブロックを消す
			this->explosion = FALSE;//火は消す
		}
	}
}

void Explosion::CheckHitBomb(Bomb *bomb)
{
	if(this->explosion == TRUE && bomb->GetFlag() == TRUE)
	{
		if(this->x+32-DHIT > bomb->GetX() && this->x+DHIT < bomb->GetX()+32 && this->y+DHIT < bomb->GetY()+32 && bomb->GetY() < this->y+32-DHIT)
		{
			this->explosion = FALSE;
			bomb->SetFlag(FALSE);
		}
	}
}

void Explosion::CheckHitItem(Item *item)
{
	if(this->explosion == TRUE && item->GetFlag() == TRUE)
	{
		if( this->x+32 > item->GetX() && this->x < item->GetX()+32 && this->y < item->GetY()+32 && this->y+32 > item->GetY() )
		{
			this->explosion = FALSE;
			item->SetFlag(FALSE);
		}
	}
}

//火が存在していれば、描く
void Explosion::Draw()
{
	if(this->explosion == TRUE)
	{
		DrawGraph(this->x, this->y,this->graph,FALSE);
	}
}

//デストラクタ
Explosion::~Explosion(void)
{
}


void Explosion::SetExplosion(int flag)
{
	this->explosion = flag;
}

int Explosion::GetExplosion()
{
	return this->explosion;
}