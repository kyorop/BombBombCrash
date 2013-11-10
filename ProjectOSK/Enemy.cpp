#include "Enemy.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#include "EnemyAI.h"
#include "Collision.h"
#include "Image.h"
#include "GameConstant.h"
#define MV 1
#define HABA 10


Enemy::Enemy(int x, int y)
	:image_left(Image::GetInstance()->GetEnemyImage(Image::LEFT)),
	image_right(Image::GetInstance()->GetEnemyImage(Image::RIGHT)),
	image_up(Image::GetInstance()->GetEnemyImage(Image::UP)),
	image_down(Image::GetInstance()->GetEnemyImage(Image::DOWN)),
	AI(new EnemyAI(*this)),
	muki(GameConst::EnemyAction::STOP),
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
		AI->Analyse(*this);

		
		switch(AI->GetAction(*this))
		{
		case GameConst::EnemyAction::STOP:
			stop = 1;
			break;
		case GameConst::EnemyAction::UP:
			this->muki = GameConst::EnemyAction::UP;
			this->y -= this->mv;
			break;
		case GameConst::EnemyAction::DOWN:
			this->muki = GameConst::EnemyAction::DOWN;
			this->y += this->mv;
			break;
		case GameConst::EnemyAction::LEFT:
			this->muki = GameConst::EnemyAction::LEFT;
			this->x -= this->mv;
			break;
		case GameConst::EnemyAction::RIGHT:
			this->muki = GameConst::EnemyAction::RIGHT;
			this->x += this->mv;
			break;
		case GameConst::EnemyAction::BOMBSET:
			this->bombSet = 1;
			break;
		case -1:
			stop = 1;
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
		case GameConst::EnemyAction::STOP:
			DrawGraph(x, y, *image_down, TRUE);break;
		case GameConst::EnemyAction::LEFT:
			DrawGraph(x, y, image_left[animpat], TRUE);break;
		case GameConst::EnemyAction::RIGHT:
			DrawGraph(x, y, image_right[animpat], TRUE);break;
		case GameConst::EnemyAction::UP:
			DrawGraph(x, y, image_up[animpat], TRUE);break;
		case GameConst::EnemyAction::DOWN:
			DrawGraph(x, y, image_down[animpat], TRUE);break;
		}
	}
}

int Enemy::EnableBomb(void)const
{
	if(bombSet == 1)
	{
		bombSet = 0;
		return 1;
	}
	else 
		return 0;
}

