#pragma once
#include "MapObject.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

namespace BombBombCrash 
{
	class MapObstacle:public MapObject
	{
	public:
		explicit MapObstacle();
		virtual ~MapObstacle();
	};
}

