#pragma once
#include "IGameProgress.h"
class BombController;

namespace BombBombCrash
{
	class Timer;
	class GameEffect : public IGameProgress
	{
	public:
		void Initialize(GameManager& game) override;
		void Update(GameManager& game) override;
		void Draw(const GameManager& game) override;
		void Destroy(const GameManager& game) override;
		bool CanRemove() override;
	private:
		int image_bombLevel;
		int image_fireLevel;
		const int white;
		const int x;
		const int y;
		BombController* bomb;
		int fpsTime[2];
		int fpsTIme_i;
		double fps;

	public:
		explicit GameEffect();
		~GameEffect(void);
	};
}