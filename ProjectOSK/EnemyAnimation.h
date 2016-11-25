#pragma once

namespace BombBombCrash
{
	class Enemy;
	class EnemyAnimation
	{

	public:

		EnemyAnimation(const Enemy& enemy);

	private:
		const Enemy& enemy;
		const int* image_left;
		const int* image_right;
		const int* image_up;
		const int* image_down;
		const int* image_death;
	};
}


