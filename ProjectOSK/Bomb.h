#pragma once
#include "MapObject.h"
#include "IColleague.h"
#include "ISoundPlayer.h"
#include "IGettable.h"
#include "Key.h"
#include "Timer.h"

class Player;
class Map;
class Charactor;
class Bomb: public MapObject, public ISoundPlayer
{
protected:
	int count;
	Timer time;
	int* image_bomb;
	int fireLevel;
	int animpat;
	mutable int soundOn;
public:
	Bomb();
	virtual ~Bomb();
	void Set(int x, int y);
	void Maintain();
	void CheckBombOverlap(const Bomb & bomb);
	void SetFlag(int flag) override;
	void Draw();
	void SetFireLevel(int level);
	int GetFireLevel()const{return fireLevel;}
	int EnableToPlaySound()const override;
};

