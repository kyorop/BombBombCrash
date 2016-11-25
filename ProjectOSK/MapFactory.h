#pragma once

namespace BombBombCrash
{
	class Block;
	class Map;
	class MapFactory
	{
	public:
		MapFactory();
		~MapFactory();

		static std::vector<std::shared_ptr<Block>> Create();
	};
}


