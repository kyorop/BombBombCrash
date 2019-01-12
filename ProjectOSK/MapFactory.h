#pragma once
#include "GameConstant.h"

namespace BombBombCrash
{
	class Block;
	class Map;
	class MapFactory
	{
		static const int map[MAP_ROW][MAP_LINE];
		ln::Vector2 ConvertToBlockPos(const int i, const int j);

	public:
		void Create();
	};
}


