#pragma once
#include "Charactor.h"

namespace BombBombCrash
{
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

	class Player;
	class EnemyAI;
	class Timer;
	class Enemy:public Character
	{
	public:
		void Update(GameManager& game) override;
		void Draw(const GameManager& game)override;
	protected:
		bool PutBomb() override;
	public:
		void Update() override;
	private:
		const int* image_left;
		const int* image_right;
		const int* image_up;
		const int* image_down;
		const int* image_death;
		int muki;
		int stop;
		int animpat;
		mutable int bombSet;
		int action[10];
		int hitNumSpeedUpItem;
		EnemyAI *const AI;
		int hasFinished;
		Timer* animationTime;
		int animationFrame;
		int speed;
	public:
		Enemy(int x, int y);
		~Enemy();

		void Move()override;
		void IncrementSpeed()override;
	};
}




