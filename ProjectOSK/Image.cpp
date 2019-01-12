#include "Image.h"

using namespace BombBombCrash;

Image::Image(void)
	:floor(),
	hardBlock(),
	softBlock(),
	item(),
	player(),
	redEnemy(),
	blackEnemy(),
	blueEnemy(),
	purpleEnemy(),
	bomb(),
	fire(),
	number(),
	colon()
{
}


Image::~Image(void)
{
}


void Image::Initialize()
{
	floor = LoadGraph("Images\\yuka.bmp");
	hardBlock = LoadGraph("Images\\rimblock.bmp");
	softBlock = LoadGraph("Images\\breakblock.bmp");
	LoadDivGraph("Images\\itemup.bmp", 3, 3, 1, 32, 32, item);
	LoadDivGraph("Images\\bombman.png", 20, 4, 5, 32, 32, player);
	LoadDivGraph("Images\\redbombman.png", 20, 4, 5, 32, 32, redEnemy);
	LoadDivGraph("Images\\blackbombman.png", 20, 4, 5, 32, 32, blackEnemy);
	LoadDivGraph("Images\\bluebombman.png", 20, 4, 5, 32, 32, blueEnemy);
	LoadDivGraph("Images\\purplebombman.png", 20, 4, 5, 32, 32, purpleEnemy);
	LoadDivGraph("Images\\bomb.png", 60, 6, 10, 32, 32, bomb);
	fire = LoadGraph("Images\\fire.bmp");
	
	//以下数字画像の読み取り簡略化コード
	char fileName[13] = "Images\\x.png";		//xには数字が来る
	for (int i = 0; i < 10; i++)
	{
		fileName[7] = i + '0';		//0のASCIIコードに数値を足せば、各数値のASCIIコードが得られる
		number[i] = LoadGraph(fileName);
	}
	colon = LoadGraph("Images\\colon.png");
}


void Image::Finalize()
{
	DeleteGraph(colon);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number[i]);
	}
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
		DeleteGraph(blueEnemy[i]);
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
		enemyColor = blueEnemy;
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
	case DEATH:
		return &enemyColor[16];
	default:
		return &enemyColor[4];
	}
}

int* Image::GetBombImage()
{
	return bomb;
}

AnimationClip Image::Load(const std::string& file_path,int all_num, int x_num, int y_num, int x_size, int y_size)
{
	auto itr = loaded_handles_.find(file_path);
	if (itr != end(loaded_handles_))
	{
		return AnimationClip(itr->second);
	}

	auto p_handles = new int[all_num];
	LoadDivGraph(file_path.c_str(), all_num, x_num, y_num, x_size, y_size, p_handles);
	std::vector<int> handles(p_handles, p_handles+all_num);
	loaded_handles_.insert(std::make_pair(file_path, handles));
	delete[] p_handles;
	return AnimationClip(handles);
}

AnimationClip Image::Load(const std::string& file_path)
{
	auto itr = loaded_handles_.find(file_path);
	if (itr != end(loaded_handles_))
	{
		return AnimationClip(itr->second);
	}

	std::vector<int> handle(1, LoadGraph(file_path.c_str()));
	loaded_handles_.insert(std::make_pair(file_path, handle));
	return AnimationClip(handle);
}
