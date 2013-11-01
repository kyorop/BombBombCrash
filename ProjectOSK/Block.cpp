#include "Block.h"
#include "Player.h"
#include "Charactor.h"
#include "MapState.h"
#include "Collision.h"
#include "DxLib.h"
#include <cstring>
#include <algorithm>
#define HABA 0
#define DHIT 5
#define KBHABA 16

Block::Block(void)
	:image_softBlock(LoadGraph("breakblock.bmp"))
{
	int temp[MAPSIZE_Y][MAPSIZE_X]=
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 1, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1,
		1, 1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 1, 1,
		1, 1, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 1, 1,
		1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	
	//IDセット
	for (int i = 0; i < GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j < GameConst::MAP_LINE; ++j)
		{
			block[i][j].SetId(temp[i][j]);
		}
	}

	//座標とフラグのセット
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			block[i][j].SetX(j * 32);
			block[i][j].SetY(i * 32);
			
			if(block[i][j].GetId() == 2)
				block[i][j].SetFlag(1);
			else
				block[i][j].SetFlag(0);
		}
	}

	//Collisionクラスへの登録
	for(int i=0; i<MAPSIZE_Y; ++i)
	{
		for(int j=0; j<MAPSIZE_X; ++j)
		{
			Collision::GetInstance()->Register(&block[i][j]);
		}
	}
}

Block::~Block(void)
{
}

void Block::Draw()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(block[i][j].GetFlag() == 1)
				DrawGraph(block[i][j].GetX(), block[i][j].GetY(), image_softBlock, FALSE);
		}
	}
}

void Block::Register()
{
	for(int i=0; i<MAPSIZE_Y; i++)
	{
		for(int j=0; j<MAPSIZE_X; j++)
		{
			if(block[i][j].GetFlag() == 1)
				MapState::GetInstance()->SetBlockState(block[i][j].GetX(), block[i][j].GetY(), 1);
			else
				MapState::GetInstance()->SetBlockState(block[i][j].GetX(), block[i][j].GetY(), 0);
		}
	}
}

int Block::IsSoftBlock(int i, int j)const
{
	return block[i][j].GetFlag();
}

