#pragma once

namespace GameConst
{
	namespace EnemyAction
	{
		enum
		{
			END = -1,
			STOP,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			BOMBREADY,
			BOMBSET,
		};
	}

	const int MAP_ROW = 13;
	const int MAP_LINE = 17;
	const int FIRST_X_LEFT = 64;
	const int FIRST_Y_UP = 32;
	const int FIRST_X_RIGHT = 32*14;
	const int FIRST_Y_DOWN = 32*11;
}