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


Bomb::Bomb(const ln::Vector2& position, int fireLevel) :
MapObject(AdjustPosition(position), 32, 32),
explosion(std::make_unique<Fire>(position)), 
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
			game.AddElement(std::make_shared<Fire>(Position()));
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

void Bomb::Destroy(const GameManager& game)
{
}

bool Bomb::CanRemove()
{
	return !Exists();
}

BombController::BombController(void):
maxSize(1)
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


void BombController::IncrementBomb(void)
{
	++maxSize;
}


int BombController::MaxSize() const
{
	return bombs.size();
}

std::shared_ptr<Bomb> BombController::Request(const ln::Vector2& position, int fireLevel)
{
	bombs.remove_if([](const std::shared_ptr<Bomb>& bomb)
	{
		return !bomb->Exists();
	});
	if (bombs.size() >= maxSize)
		return nullptr;

	auto bomb = Bomb::Create(position, fireLevel);
	bombs.push_back(bomb);
	return bomb;
}
