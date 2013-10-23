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
	void UpdateNumber();
	void Set();
public:
	CharacterSet(void);
	~CharacterSet(void);

	void Update();
	void CreateColleague() override;
	void ColleagueChange() override;

};

