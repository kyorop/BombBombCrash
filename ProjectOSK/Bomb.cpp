#include "Bomb.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "Sound.h"
#include "Explosion.h"
#define DHIT 5
#define KBHABA 16


Bomb::Bomb()
	:image_bomb(Image::GetInstance()->GetBombImage()),
	fireLevel(1),
	animpat(0),
	soundOn(0),
	explosion(std::make_unique<ExplosionManager>())
{
	flag = 0;
	x = 0;
	y = 0;
	rx = x+32;
	dy =y+32;
	Collision::GetInstance()->Register(this);
	Sound::GetInstance()->Register(this);
	MapState::GetInstance()->Register(this);
}

Bomb::~Bomb()
{
}

void Bomb::Set(int x, int y)
{
	if(flag == 0 )
	{
		//プレイヤーの重心のいるマス
		int xMasuNum = (x + x + 32) / 2 / 32;//左から何マス目か
		int yMasuNum = (y + y + 32) / 2 / 32;//上から何マス目か
		
		this->x = 32 * xMasuNum;
		this->y = 32 * yMasuNum;
		this->rx = this->x+32;
		this->dy = this->y+32;
		flag = 1;
	}
}


void Bomb::CheckBombOverlap(const Bomb &bomb)
{
	if(bomb.GetFlag() == TRUE && this->x == bomb.GetX() && this->y == bomb.GetY())
	{
		this->flag = 0;
	}
}


void Bomb::Maintain()
{	
	if(flag == 0)
		time.TurnReset();
	else
	{
		if(time.CountDownFrame(bombExistTime))//三秒たったら
		{
			flag = 0;
			soundOn = 1;
		}
	}
}


void Bomb::SetFlag(int flag)
{
	this->flag = flag;
	if(flag == FALSE)
	{
		this->time.TurnReset();
		soundOn = 1;
	}
}


void Bomb::Draw()
{
	animpat = ( (GetNowCount() & INT_MAX) / (1000 / 12)) % 3;
	if(flag == 1)
	{
		SetTransColor(255,255,255);
		DrawGraph(x, y, image_bomb[animpat], TRUE);
	}

	explosion->Draw();
}


void Bomb::SetFireLevel(int level)
{
	fireLevel = level;
}


int Bomb::EnableToPlaySound()const
{
	if(soundOn)
	{
		soundOn = 0;
		return 1;
	}
	else
		return 0;
}

void Bomb::UpFireLevel() const
{
	explosion->FireUp();
}

void Bomb::Update()
{
	Maintain();
	SetFireLevel(explosion->Firepower());
	explosion->Update(*this);
	explosion->Register();
}

BombController::BombController(void)
	:num_upFireLevel(0)
{
	bombs.push_back(std::make_unique<Bomb>());
}


BombController::~BombController(void)
{
}


void BombController::Set(int x, int y)
{
	for (int i = 0, size = bombs.size(); i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			bombs[i]->Set(x, y);
			if (i != j)
			{
				if (bombs[j]->GetFlag()
					&& bombs[j]->GetX() == bombs[i]->GetX()
					&& bombs[j]->GetY() == bombs[i]->GetY())
				{
					bombs[j]->SetFlag(false);
				}
			}
		}
	}
}


void BombController::Update(void)
{
	for (auto& bomb : bombs)
	{
		bomb->Update();
	}
}


void BombController::Draw(void)
{
	for (auto& bomb : bombs)
	{
		bomb->Draw();
	}
}


void BombController::Increment(void)
{
	auto newBomb = std::make_unique<Bomb>();

	//他の火力と同じにする
	for (int i = 0; i < num_upFireLevel; ++i)
		newBomb->UpFireLevel();

	bombs.push_back(move(newBomb));
}


void BombController::IncrementFirepower(void)
{
	for (auto& bomb : bombs)
	{
		bomb->UpFireLevel();
	}
	++num_upFireLevel;
}

int BombController::BombSize() const
{
	return bombs.size();
}

int BombController::Firepower()
{
	if (bombs.empty())
		return 0;

	return bombs[0]->GetFireLevel();
}
