#pragma once
#include "MapObject.h"
#include "IColleague.h"
#include "Key.h"
#include "Timer.h"

class Player;
class Map;
class Charactor;
class Bomb
	:public MapObject
{
protected:
	int count;
	Timer time;
	static int image_bomb[60];
	int fireLevel;
	int animpat;
public:
	Bomb();
	virtual ~Bomb();
	void Set(int x, int y);
	void Maintain();
	void CheckBombOverlap(const Bomb & bomb);
	void SetFlag(int flag) override;
	void Register();
	void Draw();
	void SetFireLevel(int level);
};

