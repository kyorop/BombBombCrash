#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Map.h"
#include "Charactor.h"
#include "DxLib.h"
#define DHIT 6
enum firestate
{
	FIREOFF,
	FIREON,
	EXPLOSION,
};


//コンストラクタ
Explosion::Explosion(int upx,int downx,int upy,int downy):
	graph( LoadGraph("fire.bmp") ), upx(upx), downx(downx), upy(upy), downy(downy)
{
}

//ボムが置かれて、それが爆発すると、火を存在させる
void Explosion::SetExplosion(const Bomb &bomb)//爆弾のあとExplosionManagerの中で一番初めに描く
{
	if(bomb.flag == 1)//ボムが置かれた
		this->flag = FIREON;

	else if(bomb.flag == 0 && this->flag == FIREON)//ボムが爆発した
	{
		if(time.CountDown(1000) == false)
		{
			this->x = bomb.x + 32*upx - 32*downx;//中心からの広がり
			this->y = bomb.y + 32*upy - 32*downy;
			this->flag = EXPLOSION;
		}
		else
			this->flag = FIREOFF;
	}
}

//プレイヤーとのあたり判定
int Explosion::CheckHItCharactor(Charactor *charactor)//ObjectのCheckHitをオーバーライド
{
	if(this->flag == EXPLOSION)//火が存在しているとき
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

	if(this->flag == EXPLOSION)
	{
		if(mapobstacle->GetID(i, j) == 1)//火が描かれる予定の場所の識別値がマップの壁なら、火を書かないようにする。
		{
			this->flag = FIREOFF;
		}
		else if(mapobstacle->GetFlag(i, j) == TRUE)//火が描かれる予定の場所の識別値が、壊れるブロックなら、そのブロックを壊して、火は描かない
		{
			mapobstacle->SetFlag(i, j, FALSE);//ブロックを消す
			this->flag = FIREOFF;//火は消す
		}
	}
}

//火が存在していれば、描く
void Explosion::Draw()
{
	if(this->flag == EXPLOSION)
	{
		DrawGraph(this->x, this->y,this->graph,FALSE);
	}
}

//デストラクタ
Explosion::~Explosion(void)
{
}

firestate Explosion::GetFlag()const
{
	return this->flag;
}

void Explosion::SetFlag(firestate flag)
{
	this->flag = flag;
}