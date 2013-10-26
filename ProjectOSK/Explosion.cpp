#include "Explosion.h"
#include "Timer.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "BombManager.h"
#include "Item.h"
#include "DxLib.h"
#define DHIT 6

//コンストラクタ
Explosion::Explosion(int center, int right,int left,int down,int up):
	graph( LoadGraph("fire.bmp") ), 
	upx(right), 
	downx(left),
	upy(down),
	downy(up),
	time(new Timer),
	fuse(0),
	explosion(0),
	isCenter(center),
	nextFire()
{
}

Explosion::~Explosion(void)
{
}

//ボムが置かれて、それが爆発すると、火を存在させる
void Explosion::Set(int x, int y)//爆弾のあとExplosionManagerの中で一番初めに描く
{
	this->x = x + 32*upx - 32*downx;//中心からの広がり
	this->y = y + 32*upy - 32*downy;
}

//プレイヤーとのあたり判定
//int Explosion::CheckHItCharactor(Charactor *charactor)//ObjectのCheckHitをオーバーライド
//{
//	if(explosion == TRUE)//火が存在しているとき
//	{
//		if(x+32-DHIT > charactor->GetX() && x+DHIT < charactor->GetRX() && y+DHIT < charactor->GetDY() && charactor->GetY() < y+32-DHIT)
//		{
//			charactor->SetCharactorState(FALSE);
//			return true;
//		}
//		else
//			return false;
//	}
//	else
//		return false;
//}
//
////壁とのあたり判定
//void Explosion::CheckHitObject(MapObstacle *mapobstacle)
//{
//	int i = y / 32;
//	int j = x / 32;
//
//	if(explosion == TRUE)
//	{
//		if(mapobstacle->GetID(i, j) == 1)//火が描かれる予定の場所の識別値がマップの壁なら、火を書かないようにする。
//		{
//			explosion = FALSE;
//		}
//		else if(mapobstacle->GetFlag(i, j) == TRUE)//火が描かれる予定の場所の識別値が、壊れるブロックなら、そのブロックを壊して、火は描かない
//		{
//			mapobstacle->SetFlag(i, j, FALSE);//ブロックを消す
//			explosion = FALSE;//火は消す
//		}
//	}
//}
//
//void Explosion::CheckHitBomb(Bomb *bomb)
//{
//	if(explosion == TRUE && bomb->GetFlag() == TRUE)
//	{
//		if(x+32-DHIT > bomb->GetX() && x+DHIT < bomb->GetX()+32 && y+DHIT < bomb->GetY()+32 && bomb->GetY() < y+32-DHIT)
//		{
//			//explosion = FALSE;
//			bomb->SetFlag(FALSE);
//			//bomb->SetFuse(1);
//		}
//	}
//}
//
//void Explosion::CheckHitItem(Item *item)
//{
//	if(explosion == TRUE && item->GetFlag() == TRUE)
//	{
//		if(x+32 > item->GetX() && x < item->GetX()+32 && y < item->GetY()+32 && y+32 > item->GetY() )
//		{
//			explosion = FALSE;
//			item->SetFlag(FALSE);
//		}
//	}
//}

void Explosion::SetExplosion(int flag)
{
	explosion = flag;
}

int Explosion::GetExplosion()
{
	return explosion;
}

//void Explosion::SetNext(Explosion *next)
//{
//	nextFire.push_back(next);
//}