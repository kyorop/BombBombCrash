#pragma once

class BombController;

namespace BombBombCrash
{
	class GameManager;
	class Timer;
	class GameEffect
	{
	public:
		void Initialize(GameManager& game);
		void Update(GameManager& game);
		void Draw(const GameManager& game);
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