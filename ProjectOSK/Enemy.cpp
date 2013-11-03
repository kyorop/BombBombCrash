#include "Enemy.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#include "EnemyAI.h"
#include "Collision.h"
#include "Image.h"
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


Enemy::Enemy(int x, int y)
	:image_left(Image::GetInstance()->GetEnemyImage(Image::LEFT)),
	image_right(Image::GetInstance()->GetEnemyImage(Image::RIGHT)),
	image_up(Image::GetInstance()->GetEnemyImage(Image::UP)),
	image_down(Image::GetInstance()->GetEnemyImage(Image::DOWN)),
	AI(new EnemyAI),
	muki(STOP),
	stop(0),
	bombSet(0)
{
	mv = MV;
	flag = 1;
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
	if(flag == 1)
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

		animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
	}
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
		SetTransColor(255,255,255);
		switch(this->muki)
		{
		case STOP:
			DrawGraph(x, y, *image_down, FALSE);break;
		case LEFT:
			DrawGraph(x, y, image_left[animpat], FALSE);break;
		case RIGHT:
			DrawGraph(x, y, image_right[animpat], FALSE);break;
		case UP:
			DrawGraph(x, y, image_up[animpat], FALSE);break;
		case DOWN:
			DrawGraph(x, y, image_down[animpat], FALSE);break;
		}
	}
}

int Enemy::EnableBomb(void)const
{
	return bombSet;
}

