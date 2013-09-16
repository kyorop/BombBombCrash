#include "EnemyBomb.h"
#include "Enemy.h"

EnemyBomb::EnemyBomb(void)
{
}

void EnemyBomb::BombSet(const Charactor &charactor)
{
	if(charactor.GetBombSet() == 1 && this->flag == 0 )//爆弾のない時にzが押されたら//zを押した時のプレイヤーの座標の取得
	{
		//プレイヤーの重心のいるマス
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//上から何マス目か
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		this->rx = this->x+32;
		this->dy = this->y+32;
		this->flag = 1;
	}
}

EnemyBomb::~EnemyBomb(void)
{
}
