#include "EnemyBomb.h"
#include "Enemy.h"

EnemyBomb::EnemyBomb(void)
{
}

void EnemyBomb::BombSet(const Charactor &charactor)
{
	if(charactor.GetBombSet() == 1 && this->flag == 0 )//���e�̂Ȃ�����z�������ꂽ��//z�����������̃v���C���[�̍��W�̎擾
	{
		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
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
