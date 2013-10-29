#include "BombSet.h"
#include "Bomb.h"
#include "ExplosionManager.h"
#include "MapState.h"

BombSet::BombSet(Bomb *bomb)
	:bomb(bomb),
	explosion(new ExplosionManager)
{
}


BombSet::~BombSet(void)
{
	delete bomb;
	delete explosion;
}

void BombSet::Register()
{
	if(bomb->GetFlag() == 0)
		MapState::GetInstance()->SetBombState(bomb->GetX(), bomb->GetY(), 0);
	else
	{
		MapState::GetInstance()->SetBombState(bomb->GetX(), bomb[i]->GetY(), 1);
		//MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), chara.GetFireLevel(), TRUE);
	}

	explosion->Register();
}

void BombSet::Set(int x, int y)
{
	bomb->BombSet(x, y);
	if(bomb->GetFlag() == 1)
		explosion->Ready(bomb->GetX(), bomb->GetY());
	else
		explosion->Set();
}


void BombSet::Update(void)
{
	Register();
	bomb->MaintainBomb();
	explosion->Maintain();
}


void BombSet::Draw(void)
{
	explosion->Draw();
}
