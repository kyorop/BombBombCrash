#pragma once
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class MapObstacle
{
protected:
	int x[MAPSIZE_Y][MAPSIZE_X];
	int rx[MAPSIZE_Y][MAPSIZE_X];
	int y[MAPSIZE_Y][MAPSIZE_X];
	int dy[MAPSIZE_Y][MAPSIZE_X];
	int flag[MAPSIZE_Y][MAPSIZE_X];
	int ID[MAPSIZE_Y][MAPSIZE_X];

public:
	void SetID(int i, int j, int id);
	int GetID(int i, int j)const;
	void SetFlag(int i, int j, int flag);
	int GetFlag(int i, int j)const;
	MapObstacle(void);
	~MapObstacle(void);
};

