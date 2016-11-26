#pragma once
#include "Charactor.h"

namespace BombBombCrash
{
#define MAPSIZE_X 17
#define MAPSIZE_Y 13


	class BombController;
	class IPlayerInput;
	class PlayerAnimation;
	class Player: public Character
	{
	public:
		void OnCollide(CollisionableObject* object) override;

		enum
		{
			LEFT,
			RIGHT,
			UP,
			DOWN,
			NOHIT,
		};
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
		const int isJoypad;
		std::unique_ptr<IPlayerInput> input;
		std::unique_ptr<BombController> bomb;
		int speed;
		int fireLevel;
		bool isWalking;
		std::unique_ptr<PlayerAnimation> animation;

	public:
		Player(const ln::Vector2& position, KeyState device);
		~Player();

		void Update() override;
		void Move()override;
		void IncrementSpeed()override;


		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;

		int Speed() override;
		int BombSize() override;
		int FireLevel() override;
		void IncrementBomb() override;
		void IncrementFireLevel() override;

		int Direction() const
		{
			return muki;
		}

		bool IsWalking()const{ return isWalking; }
		GameObjectType Type() const override { return GameObjectType::Player; }
	};
}




