#include "Map.h"
#include "DxLib.h"
#include <cstring>
#define HABA 0
#define HABA1 1

/*
const int Map::mapchip[MAPSIZE_Y][MAPSIZE_X]=
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
*/

Map::Map(void)
{
	int temp[MAPSIZE_Y][MAPSIZE_X]=
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
	std::memcpy(this->ID, temp, sizeof temp);

	this->graph[0] = LoadGraph("yuka.bmp");
	this->graph[1] = LoadGraph("rimblock.bmp");
	this->width = 32;
	this->height = 32;

	
	//壁の座標セット
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			{
				this->x[i][j] = 32 * j;
				this->rx[i][j] = this->x[i][j]+32;
				this->y[i][j] = 32 * i;
				this->dy[i][j] = this->y[i][j]+32;
			}
		}
	}
}

void Map::DrawMap()
{
	//this->mapchip[2][3] = 0;
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			//if(this->ID[i][j] == 1)
			//	DrawGraph(32 * j, 32 * i, this->graph[1],FALSE);
			//else
			//	DrawGraph(32 * j, 32 * i, this->graph[0],FALSE);
			if(this->ID[i][j] == 1)
				DrawGraph(this->x[i][j], this->y[i][j], this->graph[1],FALSE);
			else if(this->ID[i][j] == 0)
				DrawGraph(this->x[i][j], this->y[i][j], this->graph[0],FALSE);

		}
	}
}

/*
void Map::CheckHitBlock(Player *player)
{
	for(int i=0;i<MAPSIZE_Y;i++)
	{
		for(int j=0;j<MAPSIZE_X;j++)
		{
			if( (this->x[i][j] < player->x+player->width) &&
				(player->x <this->x[i][j]+this->width) &&
				(this->y[i][j] < player->y+player->height)&&
				(player->y < this->y[i][j]+this->height)     )
			{
				switch(player->muki[i][j])
				{
				case LEFT:	player->x		=	this->x[i][j]	+	player->width;break;
				case RIGHT: player->x	=	this->x[i][j]	-	player->width;break;
				case UP:		 player->y =	this->y[i][j]	+	this->height;break;
				case DOWN:player->y	=	this->y[i][j]	-	player->height;break;
				}
			}
			else
			{
				player->muki[i][j] = NOHIT;
			}
		}
	}
}
*/
Map::~Map(void)
{
}
