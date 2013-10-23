#pragma once
#include "IMediator.h"

class Player;
class BombManager;
class BlastManager;
class CharacterSet
	:public IMediator
{
private:
	Player *player;
	BombManager *bomb;
	BlastManager *fire;
	int currentSpeed;
	int currentBombNum;
	int currentFireLevel;
private:
	//プレイヤーのアイテム取得で増やす
	void UpdateNumber();
	//座標やフラグのセット
	void Set();
	//各オブジェクトの描画系の更新
	void Move();
	//全てのオブジェクトの表示
	void Draw();
public:
	CharacterSet(void);
	~CharacterSet(void);

	void Update();
	void CreateColleague() override;
	void ColleagueChange() override;

};

