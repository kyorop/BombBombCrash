#include "Map.h"
#include "GameConstant.h"

#define MAPSIZE_X 17
#define MAPSIZE_Y 13
#define DHIT 5
#define HABA 0
#define KBHABA 16
#define MV 4

namespace BombBombCrash
{ 
	Map::Map(const std::vector<std::vector<std::shared_ptr<MapObstacle>>>& sharedPtrses): 
		map(sharedPtrses)
	{
	}
}
