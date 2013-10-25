#include "EnemyBomb.h"
#include "Enemy.h"

EnemyBomb::EnemyBomb(void)
{
}

void EnemyBomb::BombSet(int x, int y)
{
	if(/*charactor.GetBombSet() == 1 &&*/ this->flag == 0 )
	{
		//プレイヤーの重心のいるマス
		int xMasuNum = (x + x + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (y + y + 32) / 2 / 32;//上から何マス目か
		
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
