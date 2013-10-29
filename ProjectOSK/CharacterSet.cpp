#include "CharacterSet.h"
#include "Player.h"
#include "BombManager.h"
#include "BlastManager.h"

CharacterSet::CharacterSet(void):
	player(new Player),
	bomb(new BombManager),
	fire(new BlastManager),
	currentSpeed(1),
	currentBombNum(1),
	currentFireLevel(1)
{
}

CharacterSet::~CharacterSet(void)
{
	delete player;
	delete bomb;
	delete fire;
}


void CharacterSet::Update()
{
	UpdateNumber();
	Set();
	Move();
}

void CharacterSet::UpdateNumber()
{
	if(currentSpeed < player->GetMV())
	{
		player->AddMV();
		++currentSpeed;
	}
	if(currentBombNum < player->GetBombNum())
	{
		bomb->Add();
		fire->Add();
		++currentBombNum;
	}
	if(currentFireLevel < player->GetFireLevel())
	{
		fire->FireLevelUp();
		++currentFireLevel;
	}
}

void CharacterSet::Set()
{
	if(player->EnableBomb() == 1)
	{
		bomb->BombSet(player->GetX(), player->GetY());
	}

	//ボムと火は一対一対応でなければならない
	for (int i = 0; i < bomb->GetAllBombNum(); ++i)
	{
		if(bomb->GetFlag( i ) == 1)
		{
			fire->Set( i , bomb->GetX( i ), bomb->GetY( i ) );
		}
	}
}

void CharacterSet::Move()
{
	player->Move();
	bomb->MaintainBomb();
	fire->Maintain();
}

void CharacterSet::Draw()
{
	//この表示の順番が大事だったり…
	bomb->Draw();
	player->Draw();
	fire->Draw();
}

