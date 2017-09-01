#pragma once
#include "GameConstant.h"

namespace BombBombCrash
{
	class Block;
	class Map;
	class MapFactory
	{
		static const int map[MAP_ROW][MAP_LINE];
		std::vector<std::shared_ptr<Block>> mapSource;
	private:
		void MakeHardblock();
		void MakeSoftBlock();
		void MakeItem();
		ln::Vector2 ConvertToBlockPos(const int i, const int j);
	public:
		MapFactory();
		~MapFactory();
		std::vector<std::shared_ptr<Block>> Create();
	};
}


