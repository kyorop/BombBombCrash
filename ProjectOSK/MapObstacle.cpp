#include "MapObstacle.h"

namespace BombBombCrash
{
	MapObstacle::MapObstacle(int id)
		:id(id)
	{
	}

	MapObstacle::~MapObstacle(void)
	{
	}

	int MapObstacle::Type()const
	{
		return id;
	}
}
