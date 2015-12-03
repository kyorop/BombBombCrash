#pragma once
#include "MapObject.h"
#include "ISoundPlayer.h"
#include "Timer.h"
#include "IDrawable.h"

class ExplosionManager;
class Player;
class Map;
class Character;
class Bomb: public MapObject, public ISoundPlayer, public IDrawable
{
	std::unique_ptr<ExplosionManager> explosion;
	static const int bombExistTime = 2500;
	
	Bomb();
protected:
	int count;
	Timer time;
	int* image_bomb;
	int fireLevel;
	int animpat;
	mutable int soundOn;
public:
	virtual ~Bomb();
	void Set(int x, int y);
	void Maintain();
	void CheckBombOverlap(const Bomb & bomb);
	void SetFlag(int flag) override;
	void Draw() override;
	void SetFireLevel(int level);
	int GetFireLevel()const{return fireLevel;}
	int EnableToPlaySound()const override;
	void UpFireLevel() const;
	void Update();

	static std::shared_ptr<Bomb> Create();
};


class BombController
{
	std::vector<std::shared_ptr<Bomb>> bombs;
	int num_upFireLevel;

public:
	BombController(void);
	~BombController(void);

	void Set(int x, int y);
	void Update(void);
	void Draw(void);
	void Increment(void);
	void IncrementFirepower(void);
	int BombSize() const;
	int Firepower();
};

