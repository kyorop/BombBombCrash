#include "Bomb.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"
#include "Sound.h"
#include "ExplosionManager.h"
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
