#pragma once
#include "MapObject.h"
#include "ICollisionable.h"
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class MapObstacle
	:public MapObject
{
public:
	enum{FLOOR, HARDBLOCK, SOFTBLOCK};
protected:
	int id;

public:
	MapObstacle(void);
	virtual ~MapObstacle(void);

	int GetId()const;
	void SetId(int id);
};

