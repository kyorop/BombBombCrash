#pragma once
#include "MapObject.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

namespace BombBombCrash 
{
	class MapObstacle:public MapObject
	{
		int id;

	public:
		enum
		{
			FLOOR, 
			HARDBLOCK, 
			SOFTBLOCK
		};

		explicit MapObstacle(int id);
		virtual ~MapObstacle();

		int Type()const;
	};
}

