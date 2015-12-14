#pragma once
#include "MapObstacle.h"

namespace BombBombCrash
{
	enum MapType;
	class Character;
	class Map
	{
		std::vector<std::vector<std::shared_ptr<MapObstacle>>> map;
	public:
		explicit Map(const std::vector<std::vector<std::shared_ptr<MapObstacle>>>& sharedPtrses);

		MapType Type();
	};
}

