#include "CharacterSet.h"
#include "Player.h"
#include "BombManager.h"
#include "BlastManager.h"

CharacterSet::CharacterSet(void):
	player(new Player),
	bomb(new BombManager),
	fire(new BlastManager),
	currentSpeed(),
	currentBombNum(),
	currentFireLevel()
{
}

void CharacterSet::Update()
{
	UpdateNumber();
	Set();
}

void CharacterSet::UpdateNumber()
{
	if(currentSpeed < player->GetMV())
	{
		player->AddSpeed();
		currentSpeed = player->GetMV();
	}
	if(currentBombNum < player->GetBombNum())
	{
		bomb->AddBomb();
		fire->Add();
		currentBombNum = player->GetBombNum();
	}
	if(currentFireLevel < player->GetFireLevel())
	{
		fire->FireUp();
		currentFireLevel = player->GetFireLevel();
	}
}

void CharacterSet::Set()
{
	if(player->EnableBomb() == 1)
	{
		bomb->BombSet(player->GetX(), player->GetY());
	}

	//�{���Ɖ΂͈�Έ�Ή��łȂ���΂Ȃ�Ȃ�
	for (int i = 0; i < bomb->GetAllBombNum(); ++i)
	{
		if(bomb->GetBombFlag( i ) == 1)
		{
			fire->Set( i , bomb->GetX( i ), bomb->GetY( i ) );
		}
	}
}

CharacterSet::~CharacterSet(void)
{
}
