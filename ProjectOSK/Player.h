#pragma once
#include "Charactor.h"
#include <memory>

#define MAPSIZE_X 17
#define MAPSIZE_Y 13


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

public:
	explicit Player(KeyState device);
	~Player();

	 void Move()override;
	 void Draw()override;
	 void AddMV()override;
	int EnableBomb()const override;
};

