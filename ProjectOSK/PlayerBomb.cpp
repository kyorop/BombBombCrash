#include "Bomb.h"
#include "PlayerBomb.h"
#include "Charactor.h"
#include "DxLib.h"

PlayerBomb::PlayerBomb(void)
{
}

void PlayerBomb::BombSet(int x, int y)
{
	if(flag == 0 )
	{
		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (x + x + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (y + y + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		rx = this->x+32;
		dy = this->y+32;
		flag = 1;
	}
}

PlayerBomb::~PlayerBomb(void)
{
}
