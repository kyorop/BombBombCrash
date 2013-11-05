#include "Image.h"
#include "DxLib.h"

Image::Image(void)
	:floor(),
	hardBlock(),
	softBlock(),
	item(),
	player(),
	enemy(),
	bomb(),
	fire()
{
}


Image::~Image(void)
{
}


void Image::Initialize()
{
	floor = LoadGraph("yuka.bmp");
	hardBlock = LoadGraph("rimblock.bmp");
	softBlock = LoadGraph("breakblock.bmp");
	LoadDivGraph("itemup.bmp", 3, 3, 1, 32, 32, item);
	LoadDivGraph("bombman.png", 20, 4, 5, 32, 32, player);
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, enemy);
	LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, bomb);
	fire = LoadGraph("fire.bmp");
}


void Image::Finalize()
{
	DeleteGraph(floor);
	DeleteGraph(hardBlock);
	DeleteGraph(softBlock);
	for (int i = 0; i < itemDivideNum; i++)
	{
		DeleteGraph(item[i]);
	}
	for (int i = 0; i < characterDivideNum; i++)
	{
		DeleteGraph(player[i]);
		DeleteGraph(enemy[i]);
	}
	for (int i = 0; i < bombDivideNum; i++)
	{
		DeleteGraph(bomb[i]);
	}
	DeleteGraph(fire);
}


int Image::GetImage(int kind)
{
	switch(kind)
	{
	case FLOOR:
		return floor;
	case HARDBLOCK:
		return hardBlock;
	case SOFTBLOCK:
		return softBlock;
	case FIRE:
		return fire;
	}
}


int Image::GetItemImage(int kind)
{
	switch(kind)
	{
	case FIREUP:
		return item[FIREUP];
	case BOMBUP:
		return item[BOMBUP];
	case SPEEDUP:
		return item[SPEEDUP];
	default:
		return item[BOMBUP];
	}
}


int* Image::GetPlayerImage(int direction)
{
	switch(direction)
	{
	case LEFT:
		return &player[8];
	case RIGHT:
		return &player[12];
	case UP:
		return &player[0];
	case DOWN:
		return &player[4];
	default:
		return &player[4];
	}
}


int* Image::GetEnemyImage(int direction)
{
	switch(direction)
	{
	case LEFT:
		return &enemy[8];
	case RIGHT:
		return &enemy[12];
	case UP:
		return &enemy[0];
	case DOWN:
		return &enemy[4];
	default:
		return &enemy[4];
	}
}


int* Image::GetBombImage()
{
	return bomb;
}
