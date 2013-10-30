#include "CharacterSet.h"
#include "Charactor.h"
#include "Player.h"
#include "BombManager.h"
#include "BlastManager.h"
#include "BombSetManager.h"

CharacterSet::CharacterSet(Charactor *pCharacter):
	character(pCharacter),
	bomb(new BombSetManager),
	currentSpeed(1),
	currentBombNum(1),
	currentFireLevel(1)
{
}

CharacterSet::~CharacterSet(void)
{
	delete character;
	delete bomb;
}

void CharacterSet::UpdateNumber()
{
	if(currentSpeed < character->GetMV())
	{
		character->AddMV();
		++currentSpeed;
	}
	if(currentBombNum < character->GetBombNum())
	{
		bomb->UpNum();
		++currentBombNum;
	}
	if(currentFireLevel < character->GetFireLevel())
	{
		bomb->UpFireLevel();
		++currentFireLevel;
	}
}

void CharacterSet::Set()
{
	if(character->EnableBomb() == 1)//z‚ª‰Ÿ‚³‚ê‚½Žž
	{
		bomb->Set(character->GetX(), character->GetY());
	}
}

void CharacterSet::Move()
{
	character->Move();
	bomb->Update();
}

void CharacterSet::Draw()
{
	//‚±‚Ì•\Ž¦‚Ì‡”Ô‚ª‘åŽ–‚¾‚Á‚½‚èc
	bomb->Draw();
	character->Draw();
}

void CharacterSet::Update()
{
	UpdateNumber();
	Move();
	Set();
}