#pragma once
#include "MapObject.h"
#include "ISoundPlayer.h"
#include "Timer.h"
#include <memory>

class ExplosionManager;
class Player;
class Map;
class Character;
class Bomb: public MapObject, public ISoundPlayer
{
private:
	std::unique_ptr<ExplosionManager> explosion;
	static const int bombExistTime = 2500;
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
	void UpFireLevel() const;
	void Update();
};

