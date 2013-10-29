#include "BlastManager.h"
#include "ExplosionManager.h"
#include "BombManager.h"
#include "MapObstacle.h"
#include "Player.h"
#include "Charactor.h"
#include "ItemManager.h"
#include "Bomb.h"
#include "MapState.h"
#include "Collision.h"
#include "DxLib.h"


BlastManager::BlastManager(void):
	blast(0),
	num_levelUp(0)
{
	ExplosionManager *em = new ExplosionManager;
	blast.push_back(em);
	Collision::GetInstance()->RegisterWithFire(em);
}

BlastManager::~BlastManager(void)
{
	std::vector<ExplosionManager*>::iterator it = blast.begin();
	for(it; it!=blast.end(); ++it)
	{
		delete *it;
	}
}

void BlastManager::FireLevelUp()
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->FireUp();
	}

	++num_levelUp;
}

void BlastManager::Add()
{
	ExplosionManager *em = new ExplosionManager;
	blast.push_back(em);
	//¡‚Ü‚Å‰Î—Í‚ğã‚°‚½•ª‚¾‚¯‰Î—Í‚ğã‚°‚é
	for (int i = 0; i < num_levelUp; ++i	)
	{
		em->FireUp();
	}

	Collision::GetInstance()->RegisterWithFire(em);	
}

void BlastManager::Set(int index, int x, int y)
{
	//for(int i=0,size=blast.size(); i<size; ++i)
	//{
		//blast[index]->Set(x, y);
	//}
}

void BlastManager::Maintain()
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->Maintain();
	}
}

void BlastManager::Draw()
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->Draw();
	}
}

void BlastManager::Register()
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->Register();
	}
}




