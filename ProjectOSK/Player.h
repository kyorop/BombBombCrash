#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IRegister.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13


class Timer;
class Player:
	public Charactor
{
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
public:	
	Player();
	~Player();

	 void Move()override;
	 void Draw()override;
	 void AddMV()override;
	int EnableBomb()const override;
};

