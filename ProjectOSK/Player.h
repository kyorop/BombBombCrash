#pragma once
#include "Charactor.h"
#include "IDrawable.h"
#include "IGameProgress.h"

namespace BombBombCrash
{
#define MAPSIZE_X 17
#define MAPSIZE_Y 13


	class BombController;
	class IPlayerInput;
	class Timer;
	class Player: public Character,public IGameProgress
	{
	protected:
		bool PutBomb() override
		{
			return false;
		}

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
		std::unique_ptr<BombController> bomb;
		int speed;
		int fireLevel;

	public:
		Player(const ln::Vector2& position, KeyState device);
		~Player();

		void Update() override;
		void Move()override;
		void IncrementSpeed()override;


		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;
		void Destroy(const GameManager& game) override;
		bool CanRemove() override;

		int Speed() override;
		int BombSize() override;
		int FireLevel() override;
		void IncrementBomb() override;
		void IncrementFireLevel() override;


	};
}




