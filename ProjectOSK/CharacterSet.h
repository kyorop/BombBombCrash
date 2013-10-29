#pragma once
#include "IMediator.h"

class Player;
class BombSetManager;
class CharacterSet
{
private:
	Player *const player;
	BombSetManager *const bomb;
	int currentSpeed;
	int currentBombNum;
	int currentFireLevel;
	int pre_i_bombSet;
	int pre_j_bombSet;
private:
	//プレイヤーのアイテム取得で増やす
	void UpdateNumber();
	//座標やフラグのセット
	void Set();
	//各オブジェクトの描画系の更新
	void Move();

public:
	CharacterSet(void);
	~CharacterSet(void);

	void Update();
	//全てのオブジェクトの表示
	void Draw();
};

