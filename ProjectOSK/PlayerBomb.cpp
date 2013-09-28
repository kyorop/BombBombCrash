#include "Bomb.h"
#include "PlayerBomb.h"
#include "Charactor.h"
#include "DxLib.h"

PlayerBomb::PlayerBomb(void)
{
}

void PlayerBomb::BombSet(const Charactor &charactor)
{
	if(CheckHitKey(KEY_INPUT_Z) && this->flag == 0 )
	{
		
		//�v���C���[�̏d�S�̂���}�X
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//�����牽�}�X�ڂ�
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//�ォ�牽�}�X�ڂ�
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		this->rx = this->x+32;
		this->dy = this->y+32;
		this->flag = 1;

		//if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
		//	this->flag = 0;
	}
}

PlayerBomb::~PlayerBomb(void)
{
}