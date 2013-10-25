#include "Map.h"
#include "Player.h"
#include "DxLib.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include <cstring>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13
#define DHIT 5
#define HABA 0
#define KBHABA 16
#define MV 4

Map::Map(void):
	floor(LoadGraph("yuka.bmp")),
	hardBlock(LoadGraph("rimblock.bmp")),
	softBlock(LoadGraph("breakblock.bmp")),
	map()
{
	int temp[MAPSIZE_Y][MAPSIZE_X]=
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
		1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
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
			if(map[i][j].GetId() != 0)
				map[i][j].SetFlag(1);
		}
	}

	for(int i=0; i<MAPSIZE_Y; ++i)
	{
		for(int j=0; j<MAPSIZE_X; ++j)
		{
			Collision::GetInstance()->Register(&map[i][j]);
		}
	}
}

Map::~Map(void)
{
}

void Map::Draw()
{
	//床と強ブロックは常に表示
	//しかし最初に弱ブロックがある場合、それがなくなった後は床を表示する必要がある
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(map[i][j].GetId() == 1)
				DrawGraph(map[i][j].GetX(), map[i][j].GetY(), hardBlock, FALSE);
			else if(map[i][j].GetId() == 2)
			{
				if(map[i][j].GetFlag() == 1)
					DrawGraph(map[i][j].GetX(), map[i][j].GetY(), softBlock, FALSE);
				else
					DrawGraph(map[i][j].GetX(), map[i][j].GetY(), floor, FALSE);
			}
			else
				DrawGraph(map[i][j].GetX(), map[i][j].GetY(), floor, FALSE);
		}
	}
}

void Map::Register()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(map[i][j].GetId() == 0 || (map[i][j].GetId() == 2 && map[i][j].GetFlag() == 0))
				MapState::GetInstance()->SetMapState(map[i][j].GetX(), map[i][j].GetY(), 0);
			else if(map[i][j].GetId() == 1)
				MapState::GetInstance()->SetMapState(map[i][j].GetX(), map[i][j].GetY(), 1);
			else if(map[i][j].GetId() == 2)
			{
				if(map[i][j].GetFlag() == 1)
					MapState::GetInstance()->SetBlockState(map[i][j].GetX(), map[i][j].GetY(), 1);
				else
					MapState::GetInstance()->SetBlockState(map[i][j].GetX(), map[i][j].GetY(), 0);

			}
		}
	}
}



