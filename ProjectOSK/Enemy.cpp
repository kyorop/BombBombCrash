#include "Enemy.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#define MV 3
#define HABA 10
#define ROW 13
#define LINE 17

enum object
{
	MAP,
	BLOCK,
	ITEM,
	CHARACTOR,
	BOMB,
	FIRE,
};

enum
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

Enemy::Enemy(int x, int y)
{
	this->mv = MV;
	this->flag = TRUE;
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, this->graph, FALSE);
	this->x = x;
	this->y = y;
	this->resetRoutine = 1;
	this->muki = STOP;
}


Enemy::~Enemy(void)
{
}

void Enemy::Analyse()
{
	MapState *ms = MapState::GetInstance();
	for(int k=-1; k<2; ++k)
	{
		//if( !(this->x/32+k < 0 || LINE < this->x/32+k || this->y/32+k < 0 || ROW < this->y/32+k) )
		{
			if( MapState::GetInstance()->GetState(this->y/32,this->x/32+k, BLOCK) == 0 ||ms->GetState(this->x/32+k,this->y/32, MAP) == 0)
			{
				if(k>0)
					this->muki = RIGHT;
				else
					this->muki = LEFT;
			}
			if( MapState::GetInstance()->GetState(this->y/32+k, this->x/32, BLOCK) == 0 || ms->GetState(this->y/32+k, this->x/32, MAP) == 0)
			{
				if(k>0)
					this->muki = DOWN;
				else
					this->muki = UP;
			}
		}
	}

	this->resetRoutine = 0;
}

void Enemy::Move(int g_lastTime, const Player &player)
{
	if(this->resetRoutine == 0)
	{
		switch(this->muki)
		{
		case UP:this->y -= this->mv;break;
		case DOWN:this->y += this->mv;break;
		case LEFT:this->x -= this->mv;break;
		case RIGHT:this->x += this->mv;break;
		}
		
		if(this->x % 32 == 0 && this->y % 32 == 0)
		{
			this->muki = STOP;
			this->resetRoutine = 1;
		}
	}
		
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
