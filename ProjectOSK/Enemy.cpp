#include "Enemy.h"
#include "MapState.h"
#include "EnemyAI.h"
#include "Collision.h"
#include "Image.h"
#include "GameConstant.h"
#include "Timer.h"

using namespace BombBombCrash;

bool Enemy::PutBomb()
{
	if (bombSet == 1)
	{
		bombSet = 0;
		return 1;
	}
	else
		return 0;
}

void Enemy::Update()
{
	Move();
	PutBomb();
}

Enemy::Enemy(int x, int y)
	:image_left(Image::GetInstance()->GetCharacterImage(id, Image::LEFT)),
	image_right(Image::GetInstance()->GetCharacterImage(id, Image::RIGHT)),
	image_up(Image::GetInstance()->GetCharacterImage(id, Image::UP)),
	image_down(Image::GetInstance()->GetCharacterImage(id, Image::DOWN)),
	image_death(Image::GetInstance()->GetCharacterImage(id, Image::DEATH)),
	AI(new EnemyAI(*this)),
	muki(GameConst::EnemyAction::STOP),
	stop(0),
	bombSet(0),
	hitNumSpeedUpItem(1),
	hasFinished(0),
	animationTime(new Timer),
	animationFrame(0),
	speed(1)
{
	SetPosition(ln::Vector2(x, y));
	Collision::Instance()->Register(this);
	MapState::GetInstance()->RegisterWithCharacter(this);
}

Enemy::~Enemy(void)
{
	delete animationTime;
	delete AI;
}

void Enemy::Move()
{
	if(Exists())
	{
		AI->Analyse(*this);

		
		switch(AI->GetAction(*this))
		{
		case GameConst::EnemyAction::STOP:
			stop = 1;
			break;
		case GameConst::EnemyAction::UP:
			this->muki = GameConst::EnemyAction::UP;
			Translate(ln::Vector2(0, -speed));
			break;
		case GameConst::EnemyAction::DOWN:
			this->muki = GameConst::EnemyAction::DOWN;
			Translate(ln::Vector2(0, speed));
			break;
		case GameConst::EnemyAction::LEFT:
			this->muki = GameConst::EnemyAction::LEFT;
			Translate(ln::Vector2(-speed, 0));
			break;
		case GameConst::EnemyAction::RIGHT:
			this->muki = GameConst::EnemyAction::RIGHT;
			Translate(ln::Vector2(speed, 0));
			break;
		case GameConst::EnemyAction::BOMBSET:
			this->bombSet = 1;
			break;
		case -1:
			stop = 1;
			break;
		}

		auto pos = Position();
		if (pos.X < 64)
			SetPosition(ln::Vector2(64, pos.Y));
		if (pos.X > 32 * 14)
			SetPosition(ln::Vector2(32 * 14, pos.Y));
		if (pos.Y < 32)
			SetPosition(ln::Vector2(pos.X, 32));
		if (pos.Y > 32 * 11)
			SetPosition(ln::Vector2(pos.X, 32 * 11));

		animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
	}
}

void Enemy::Draw(void)
{
	if(Exists())
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
			DrawGraph(Position().X, Position().Y, *image_down, TRUE);break;
		case GameConst::EnemyAction::LEFT:
			DrawGraph(Position().X, Position().Y, image_left[animpat], TRUE);break;
		case GameConst::EnemyAction::RIGHT:
			DrawGraph(Position().X, Position().Y, image_right[animpat], TRUE);break;
		case GameConst::EnemyAction::UP:
			DrawGraph(Position().X, Position().Y, image_up[animpat], TRUE);break;
		case GameConst::EnemyAction::DOWN:
			DrawGraph(Position().X, Position().Y, image_down[animpat], TRUE);break;
		}
	}
	else
	{
		if( !hasFinished )
		{
			if(animationTime->CountDownFrame(600))
			{
				++animationFrame;
				if(animationFrame == 3)
					hasFinished =1;
			}
			DrawGraph(Position().X, Position().Y, image_death[animationFrame], true);
		}
	}
}

void Enemy::IncrementSpeed()
{
	if(speed < 4)
	{
		++hitNumSpeedUpItem;
		if(32%(speed+1) == 0)
			++speed;
		else if(32%hitNumSpeedUpItem == 0)
			speed = hitNumSpeedUpItem;
	}
}