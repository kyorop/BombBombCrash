#pragma once
#include "MapObject.h"
#include "ISoundPlayer.h"
#include "IGameProgress.h"

namespace BombBombCrash
{
	class Timer;
	class Fire;
	class Player;
	class Map;
	class Character;

	class Bomb: public MapObject, public ISoundPlayer, public IGameProgress
	{
		static const int bombExistTime = 2500;

		std::unique_ptr<Fire> explosion;
		std::unique_ptr<Timer> timer;
		int count;
		int* image_bomb;
		int animpat;
		mutable int soundOn;

		explicit Bomb(const ln::Vector2& position, int fireLevel);
		
		ln::Vector2 AdjustPosition(const ln::Vector2& position) const;
	
	public:
		void IncrementFire() const;
		
		int EnableToPlaySound()const override;

		static std::shared_ptr<Bomb> Create(const ln::Vector2& position, int fireLevel);

		void Initialize(GameManager& game) override;

		void Update(GameManager& game) override;
		
		void Draw(const GameManager& game) override;
		
		void Destroy(const GameManager& game) override;
		
		bool CanRemove() override;
	};
}


namespace BombBombCrash
{
	class BombController
	{
		std::list<std::shared_ptr<Bomb>> bombs;
		int maxSize;

	public:
		BombController(void);

		std::shared_ptr<Bomb> Request(const ln::Vector2& position, int fireLevel);
		void IncrementBomb();
		int MaxSize() const;
	};
}




