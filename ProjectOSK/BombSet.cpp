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
	{
		int x_center = (x + x+32) / 2;
		int y_center = (y + y+32) / 2;
		int i = y_center / 32;
		int j = x_center / 32;
		if(MapState::GetInstance()->GetState(i, j, BOMB) == 0)
		{
			bomb->Set(x, y);
			explosion->Ready(bomb->GetX(), bomb->GetY());
		}
	}
}

void BombSet::Update(void)
{
	bomb->Register();
	explosion->Register();
	
	bomb->Maintain();
	explosion->Maintain();
	
	if(bomb->GetFlag() == 0)
		explosion->Set();
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
