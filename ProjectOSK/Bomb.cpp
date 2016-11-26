#include "Bomb.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "Sound.h"
#include "Explosion.h"
#include "Timer.h"
#include "GameManager.h"
#define DHIT 5
#define KBHABA 16

using namespace BombBombCrash;


void Bomb::OnCollide(CollisionableObject* object)
{
}

Bomb::Bomb(const ln::Vector2& position, int fireLevel) :
CollisionableObject(AdjustPosition(position), 32, 32),
explosion(std::make_unique<BombBombCrash::Fire>(position)), 
timer(std::make_unique<Timer>()),
count(0),
image_bomb(Image::GetInstance()->GetBombImage()),
animpat(0),
soundOn(0)
{
	Collision::Instance()->Register(this);
	Sound::GetInstance()->Register(this);
	MapState::GetInstance()->Register(this);
}


ln::Vector2 Bomb::AdjustPosition(const ln::Vector2& position) const
{
	//プレイヤーの重心のいるマス
	int xMasuNum = (position.X + position.X + 32) / 2 / 32;//左から何マス目か
	int yMasuNum = (position.Y + position.Y + 32) / 2 / 32;//上から何マス目か

	auto newPos = ln::Vector2(32 * xMasuNum, 32 * yMasuNum);
	return newPos;
}

//void Bomb::Maintain()
//{	
//	if(!Exists())
//		timer->TurnReset();
//	else
//	{
//		if (timer->CountDownFrame(bombExistTime))//三秒たったら
//		{
//			exists = 0;
//			soundOn = 1;
//		}
//	}
//}

//void Bomb::SetExists(int flag)
//{
//	this->exists = flag;
//	if(flag == FALSE)
//	{
//		this->timer->TurnReset();
//		soundOn = 1;
//	}
//}

int Bomb::EnableToPlaySound()const
{
	if(soundOn)
	{
		soundOn = 0;
		return 1;
	}
	
	return 0;
}

std::shared_ptr<Bomb> Bomb::Create(const ln::Vector2& position, int fireLevel)
{
	auto bomb = new Bomb(position, fireLevel);
	bomb->SetExists(false);
	return std::shared_ptr<Bomb>(bomb);
}

void Bomb::IncrementFire() const
{
}

void Bomb::Initialize(GameManager& game)
{
	timer->TurnReset();
}

void Bomb::Update(GameManager& game)
{
	if (Exists())
	{
		if (timer->CountDownFrame(bombExistTime))
		{
//			game.AddElement(std::make_shared<Fire>(Position()));
			SetExists(false);
		}
	}

	explosion->Register();
}

void Bomb::Draw(const GameManager& game)
{
	animpat = ((GetNowCount() & INT_MAX) / (1000 / 12)) % 3;
	if (Exists())
	{
		SetTransColor(255, 255, 255);
		auto pos = Position();
		DrawGraph(pos.X, pos.Y, image_bomb[animpat], TRUE);
	}
}


BombController::BombController(void)
{
}


//void BombController::Set(int x, int y)
//{
//	for (int i = 0, size = bombs.size(); i < size; ++i)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			bombs[i]->Set(x, y);
//			if (i != j)
//			{
//				if (bombs[j]->Exists()
//					&& bombs[j]->GetX() == bombs[i]->GetX()
//					&& bombs[j]->GetY() == bombs[i]->GetY())
//				{
//					bombs[j]->SetExists(false);
//				}
//			}
//		}
//	}
//}


void BombController::IncrementBomb(int fireLevel)
{
	bombs.push_back(Bomb::Create(ln::Vector2(), fireLevel));
}


int BombController::MaxSize() const
{
	return bombs.size();
}

std::shared_ptr<Bomb> BombController::Request(const ln::Vector2& position, int fireLevel)
{
	for (auto itr = begin(bombs); itr != end(bombs); ++itr)
	{
		if (!(*itr)->Exists())
		{
			(*itr)->SetExists(true);
			(*itr)->SetPosition(position);
			return *itr;
		}
	}

	return nullptr;
}
