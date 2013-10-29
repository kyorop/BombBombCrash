#include "CharacterSet.h"
#include "Player.h"
#include "BombManager.h"
#include "BlastManager.h"
#include "BombSetManager.h"

CharacterSet::CharacterSet(void):
	player(new Player),
	bomb(new BombSetManager),
	currentSpeed(1),
	currentBombNum(1),
	currentFireLevel(1)
{
}

CharacterSet::~CharacterSet(void)
{
	delete player;
	delete bomb;
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
		bomb->UpNum();
		++currentBombNum;
	}
	if(currentFireLevel < player->GetFireLevel())
	{
		bomb->UpFireLevel();
		++currentFireLevel;
	}
}

void CharacterSet::Set()
{
	if(player->EnableBomb() == 1)//z�������ꂽ��
	{
		bomb->Set(player->GetX(), player->GetY());
	}
}

void CharacterSet::Move()
{
	player->Move();
	bomb->Update();
}

void CharacterSet::Draw()
{
	//���̕\���̏��Ԃ��厖��������c
	bomb->Draw();
	player->Draw();
}

void CharacterSet::Update()
{
	UpdateNumber();
	Set();
	Move();
}