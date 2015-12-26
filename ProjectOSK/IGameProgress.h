#pragma once

namespace BombBombCrash
{
	class GameManager;
	interface IGameProgress
	{
		virtual void Initialize(GameManager& game)=0;
		virtual void Update(GameManager& game) = 0;
		virtual void Draw(const GameManager& game) = 0;
		virtual void Destroy(const GameManager& game) = 0;
		virtual bool CanRemove() = 0;

		virtual ~IGameProgress()
		{
		}
	};
}


