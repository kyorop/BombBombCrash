#include "MapObstacle.h"
#include "Collision.h"

MapObstacle::MapObstacle(void)
	:id()
{
}

MapObstacle::~MapObstacle(void)
{
}

void MapObstacle::SetId(int id)
{
	this->id = id;
}

int MapObstacle::GetId()const
{
	return id;
}