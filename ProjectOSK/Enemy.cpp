#include "Enemy.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#include "EnemyAI.h"
#include "Collision.h"
#define MV 1
#define HABA 10

enum
{
	END = -1,
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BOMBSET,
	BOMBSETOFF,
};


Enemy::Enemy(int x, int y):
	AI(new EnemyAI),
	muki(STOP),
	stop(0),
	bombSet(0)
{
	mv = MV;
	flag = 1;
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, this->graph, FALSE);
	this->x = x;
	this->y = y;
	Collision::GetInstance()->Register(this);
}

Enemy::~Enemy(void)
{
	delete AI;
}

void Enemy::Move()
{
	AI->Analyse(this->y/32, this->x/32, *this);

	bombSet = 0;
	switch(AI->GetAction(*this))
	{
	case STOP:
		stop = 1;
		break;
	case UP:
		this->muki = UP;
		this->y -= this->mv;
		break;
	case DOWN:
		this->muki = DOWN;
		this->y += this->mv;
		break;
	case LEFT:
		this->muki = LEFT;
		this->x -= this->mv;
		break;
	case RIGHT:
		this->muki = RIGHT;
		this->x += this->mv;
		break;
	case BOMBSET:
		this->bombSet = 1;
		break;
	case BOMBSETOFF:
		break;
	case -1:
		break;
	}

	if(this->x < 64)this->x = 64;
	if(this->x > 32*14)this->x = 32*14;
	if(this->y < 32)this->y = 32;
	if(this->y > 32*11)this->y = 32*11;

	this->rx = this->x+32;
	this->dy = this->y+32;

	//this->animpat = (g_lastTime / (1000 / 12)) % 4;
	animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
}

void Enemy::Draw(void)
{

	if(this->flag == 1)
	{
		if(stop == 1)
		{
			animpat = 0;
			stop = 0;
		}
		switch(this->muki)
		{
		case STOP:
			DrawGraph(this->x, this->y, this->graph[4], TRUE);break;
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
}

int Enemy::EnableBomb(void)const
{
	return bombSet;
}

