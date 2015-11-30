#pragma once
#include "Charactor.h"
#include <memory>

#define MAPSIZE_X 17
#define MAPSIZE_Y 13


class BombSetManager;
class IPlayerInput;
class Timer;
class Player: public Charactor
{
public:
	enum KeyState
	{
		KEYBORAD,
		JOYPAD,
	};

private:
	int muki;
	int animpat;
	const int* image_left;
	const int* image_right;
	const int* image_up;
	const int* image_down;
	const int* image_death;
	int hasFinished;
	Timer* animationTime;
	int animationFrame;
	const int isJoypad;
	std::unique_ptr<IPlayerInput> input;
	std::unique_ptr<BombSetManager> bomb;

public:
	explicit Player(KeyState device);
	~Player();

	 void Draw()override;
	 void Update() override;
	 void Move()override;
	 void SetMv()override;
	 bool PutBomb() override;
};

