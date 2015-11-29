#include "Map.h"
#include "Player.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include <cstring>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13
#define DHIT 5
#define HABA 0
#define KBHABA 16
#define MV 4

Map::Map(void)
	:map(),
	image_floor(Image::GetInstance()->GetImage(Image::FLOOR)),
	image_hardBlock(Image::GetInstance()->GetImage(Image::HARDBLOCK))
{
	int temp[MAPSIZE_Y][MAPSIZE_X]=
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j < GameConst::MAP_LINE; ++j)
		{
			map[i][j].SetId(temp[i][j]);
		}
	}

	//壁の座標セット
	for(int i=0; i<MAPSIZE_Y; ++i)
	{
		for(int j=0; j<MAPSIZE_X; ++j)
		{
			map[i][j].SetX(j * 32);
			map[i][j].SetY(i * 32);
			if(map[i][j].GetId() == MapObstacle::FLOOR || map[i][j].GetId() == MapObstacle::HARDBLOCK)
				map[i][j].SetFlag(1);
		}
	}

	for(int i=0; i<MAPSIZE_Y; ++i)
	{
		for(int j=0; j<MAPSIZE_X; ++j)
		{
			if(map[i][j].GetId() == 1)
				Collision::GetInstance()->Register(&map[i][j]);
		}
	}
}

Map::~Map(void)
{
}

void Map::Draw()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(map[i][j].GetId() == MapObstacle::FLOOR)
				DrawGraph(map[i][j].GetX(), map[i][j].GetY(), image_floor, FALSE);
			else
				DrawGraph(map[i][j].GetX(), map[i][j].GetY(), image_hardBlock, FALSE);
		}
	}
}

void Map::Register()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(map[i][j].GetId() == MapObstacle::HARDBLOCK)
			{
				if(map[i][j].GetFlag() == 1)
					MapState::GetInstance()->SetMapState(map[i][j].GetX(), map[i][j].GetY(), 1);
				else
					MapState::GetInstance()->SetMapState(map[i][j].GetX(), map[i][j].GetY(), 0);
			}
			else
			{
				MapState::GetInstance()->SetMapState(map[i][j].GetX(), map[i][j].GetY(), 0);
			}
		}
	}
}



