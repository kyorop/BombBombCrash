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
		
		//プレイヤーの重心のいるマス
		int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//上から何マス目か
		
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
