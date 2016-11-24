#pragma once

namespace BombBombCrash{
	class Timer;
	class Player;

	class PlayerAnimation
	{
	public:
		explicit PlayerAnimation(const Player& player);

		void Walk();
		void Killed();
	private:
		const Player& player;
		const int* image_left;
		const int* image_right;
		const int* image_up;
		const int* image_down;
		const int* image_death;
		int animpat;
		std::unique_ptr<Timer> deathAnimTimer;
		int deathAnimFrame;
		ln::Vector2 killedPos;
	};
}


