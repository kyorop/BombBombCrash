#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#define MV 1
#define HABA 10
enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

Enemy::Enemy(int x, int y)
{
	this->flag = TRUE;
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, this->graph, FALSE);
	this->x = x;
	this->y = y;
	this->preX = x;
	this->preY = y;
}


Enemy::~Enemy(void)
{
}


void Enemy::Move(int g_lastTime, const Player &player)
{
	if(player.GetX() - this->x >= 0)
	{
		this->x += MV;
		this->muki = RIGHT;
	}
	else
	{
		this->x -= MV;
		this->muki = LEFT;
	}
	if(player.GetY() - this->y >= 0)
	{
		this->y += MV;
		this->muki = DOWN;
	}
	else
	{
		this->y -= MV;
		this->muki = UP;
	}
	/*
	switch((g_lastTime / 1000*3) % 4)
	{
	case 0:
		this->x += MV;
		this->muki = RIGHT;
		
	case 1:
		this->x -= MV;
		this->muki = LEFT;
		break;

	case 2:
		this->y += MV;
		this->muki = DOWN;
		break;

	case 3:
		this->y -= MV;
		this->muki = UP;
		break;
	}
	*/

	/*
	this->preX = this->x;
	this->preY = this->y;
	++this->x;
	if(this->x >= preX)
	{
		++this->x;
		this->muki = RIGHT;
	}
	
	if(this->x == this->preX)
	{
		--this->x;
		this->muki = LEFT;
	}
	if(this->preY - HABA <this->y && this->y < this->preY + HABA)
	{
		--this->y;
		this->muki = UP;
	}
	else
	{
		++this->y;
		this->muki = DOWN;
	}
	*/

	if(this->x < 64)this->x = 64;
	if(this->x > 32*14)this->x = 32*14;
	if(this->y < 32)this->y = 32;
	if(this->y > 32*11)this->y = 32*11;

	this->animpat = (g_lastTime / (1000 / 12)) % 4;
}

void Enemy::Draw(void)
{
	switch(this->muki)
	{
	case LEFT:
		DrawGraph(this->x, this->y, this->graph[animpat+8], TRUE);break;
	case RIGHT:
		DrawGraph(this->x, this->y, this->graph[animpat+12], TRUE);break;
	case UP:
		DrawGraph(this->x, this->y, this->graph[animpat+0], TRUE);break;
	case DOWN:
		DrawGraph(this->x, this->y, this->graph[animpat+4], TRUE);	break;
	}
}
