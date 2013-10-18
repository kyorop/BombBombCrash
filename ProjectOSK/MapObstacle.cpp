#include "MapObstacle.h"

MapObstacle::MapObstacle(void)
{
}

void MapObstacle::SetID(int i, int j, int id)
{
	this->ID[i][j] = id;
}

int MapObstacle::GetID(int i, int j)const
{
	return this->ID[i][j];
}
 
void MapObstacle::SetFlag(int i, int j, int flag)
{
	this->flag[i][j] = flag;
}

int MapObstacle::GetFlag(int i, int j)const
{
	return this->flag[i][j];
}

MapObstacle::~MapObstacle(void)
{
}
