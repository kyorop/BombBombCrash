#include "Bomb.h"
#include "PlayerBomb.h"
#include "Charactor.h"
#include "DxLib.h"

PlayerBomb::PlayerBomb(void)
{
}

void PlayerBomb::BombSet(int x, int y)
{
	//if(CheckHitKey(KEY_INPUT_Z) && this->flag == 0 )
	//{
	//	
	//	//プレイヤーの重心のいるマス
	//	int xMasuNum = (charactor.GetX() + charactor.GetX() + 32) / 2 / 32;//左から何マス目か
	//	int yMasuNum = (charactor.GetY() + charactor.GetY() + 32) / 2 / 32;//上から何マス目か
	//	
	//	this->x = 32 * xMasuNum;
	//	this->y = 32 * yMasuNum;
	//	this->rx = this->x+32;
	//	this->dy = this->y+32;
	//	this->flag = 1;

	//	//if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
	//	//	this->flag = 0;
	//}

	//if( CheckHitKey(KEY_INPUT_Z) == 1 && this->flag == 0 )//爆弾のない時にzが押されたら//zを押した時のプレイヤーの座標の取得
	if(flag == 0 )
	{
		//プレイヤーの重心のいるマス
		int xMasuNum = (x + x + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (y + y + 32) / 2 / 32;//上から何マス目か
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		rx = this->x+32;
		dy = this->y+32;
		flag = 1;

		//if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
		//	this->flag = 0;
	}
}

PlayerBomb::~PlayerBomb(void)
{
}
