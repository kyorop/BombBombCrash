#include "MapObstacle.h"
#include "Collision.h"

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
