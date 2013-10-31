#pragma once
#include "IMediator.h"

class Charactor;
class BombSetManager;
class CharacterSet
{
private:
	Charactor *const character;
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
public:
	CharacterSet(Charactor *character);
	~CharacterSet(void);

	void Update();
	//全てのオブジェクトの表示
	void Draw();
};

