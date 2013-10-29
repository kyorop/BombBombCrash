#include "BombSet.h"
#include "Bomb.h"
#include "ExplosionManager.h"
#include "MapState.h"

BombSet::BombSet()
	:bomb(new Bomb),
	explosion(new ExplosionManager)
{
}


BombSet::~BombSet(void)
{
	delete bomb;
	delete explosion;
}


void BombSet::Set(int x, int y)
{
	if(bomb->GetFlag() == 0)
		bomb->Set(x, y);
}

void BombSet::Update(void)
{
	bomb->Register();
	explosion->Register();
	bomb->Maintain();
	explosion->Update(*bomb);
	
}

void BombSet::Draw(void)
{
	bomb->Draw();
	explosion->Draw();
}

void BombSet::UpFireLevel(void)
{
	explosion->FireUp();
}

int BombSet::GetBombX()const
{
	return bomb->GetX();
}

int BombSet::GetBombY()const
{
	return bomb->GetY();
}

int BombSet::GetFlag()const
{
	return bomb->GetFlag();
}

void BombSet::SetFlag(int flag)
{
	bomb->SetFlag(flag);
}