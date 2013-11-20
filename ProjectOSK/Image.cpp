#include "Image.h"
#include "DxLib.h"

Image::Image(void)
	:floor(),
	hardBlock(),
	softBlock(),
	item(),
	player(),
	redEnemy(),
	blackEnemy(),
	greenEnemy(),
	purpleEnemy(),
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
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, redEnemy);
	LoadDivGraph("blackbombman.png", 20, 4, 5, 32, 32, blackEnemy);
	LoadDivGraph("greenbombman.png", 20, 4, 5, 32, 32, greenEnemy);
	LoadDivGraph("purplebombman.png", 20, 4, 5, 32, 32, purpleEnemy);
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
		DeleteGraph(redEnemy[i]);
		DeleteGraph(blackEnemy[i]);
		DeleteGraph(greenEnemy[i]);
		DeleteGraph(purpleEnemy[i]);
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


int* Image::GetCharacterImage(int id, int direction)
{
	int* enemyColor;
	switch(id)
	{
	case 0:
		enemyColor = player;
		break;
	case 1:
		enemyColor = blackEnemy;
		break;
	case 2:
		enemyColor = redEnemy;
		break;
	case 3:
		enemyColor = greenEnemy;
		break;
	case 4:
		enemyColor = purpleEnemy;
		break;
	default:
		enemyColor = redEnemy;
		break;
	}
	switch (direction)	
	{
	case LEFT:
		return &enemyColor[8];
	case RIGHT:
		return &enemyColor[12];
	case UP:
		return &enemyColor[0];
	case DOWN:
		return &enemyColor[4];
	default:
		return &enemyColor[4];
	}
}


int* Image::GetBombImage()
{
	return bomb;
}
