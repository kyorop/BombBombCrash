#include "EnemyBomb.h"
#include "Enemy.h"

EnemyBomb::EnemyBomb(void)
{
}

void EnemyBomb::BombSet(int x, int y)
{
	if(/*charactor.GetBombSet() == 1 &&*/ this->flag == 0 )
	{
		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (x + x + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (y + y + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
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
