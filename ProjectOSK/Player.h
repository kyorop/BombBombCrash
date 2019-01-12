#pragma once
#include "Charactor.h"
#include "ICharacterAction.h"
#include "Animator.h"
#include "BombBag.h"
#include "IPlayerInput.h"
namespace BombBombCrash
{
	class BombController;
	class IPlayerInput;
	class PlayerAnimation;
	class Player final : public Character, public ICharacterAction
	{
	public:

		enum
		{
			LEFT,
			RIGHT,
			UP,
			DOWN,
		};

		enum KeyState
		{
			KEYBORAD,
			JOYPAD,
		};

	private:
		const int isJoypad;
		std::unique_ptr<IPlayerInput> input;
		std::unique_ptr<Animator> walking_animation_;
		std::shared_ptr<BombBag> bomb_bag_;
		std::list<int> on_bomb_ids_;

	public:
		Player(const ln::Vector2& position, KeyState device);

		void Move()override;
		void PutBomb()override;
		
		void Initialize() override;
		void Update() override;
		void Draw() override;
		void Finalize() override{}

		ObjectType Type()const override;
		void OnCollide(MapObject& other) override;
		void OnCollisionExit(MapObject& other) override;
	};
}




