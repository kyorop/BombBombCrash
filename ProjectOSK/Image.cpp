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
	LoadDivGraph("itemup.bmp", 3, 3, 1, 32, 32, item, FALSE);
	LoadDivGraph("bombman.png", 20, 4, 5, 32, 32, player, FALSE);
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, enemy, FALSE);
	LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, bomb, FALSE);
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
		return item[kind];
	case SPEEDUP:
		return item[SPEEDUP];
	}
}


int Image::GetCharacterImage(int direction)
{
	switch(direction)
	{
	case LEFT:
		return player[8];
	case RIGHT:
		return player[12];
	case UP:
		return player[0];
	case DOWN:
		return player[4];
	}
}
