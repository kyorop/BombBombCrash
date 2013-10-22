#include "BlastManager.h"
#include "ExplosionManager.h"
#include "BombManager.h"
#include "MapObstacle.h"
#include "Player.h"
#include "Charactor.h"
#include "ItemManager.h"
#include "Bomb.h"
#include "MapState.h"
#include "DxLib.h"


BlastManager::BlastManager(void):
	blast(0),
	nowBlastNum(1)
{
	blast.push_back(new ExplosionManager);
}

BlastManager::~BlastManager(void)
{
	std::vector<ExplosionManager*>::iterator it = blast.begin();
	for(it; it!=blast.end(); ++it)
	{
		delete *it;
	}
}

void BlastManager::FireUp(const Charactor &charactor)const
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->FireUp(charactor);
	}
}

void BlastManager::Add(const Charactor &charactor)
{
	if(charactor.GetBombNum() > this->nowBlastNum)
	{
		blast.push_back(new ExplosionManager);
		++this->nowBlastNum;
	}
}

void BlastManager::Set(const BombManager &bombManager)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->Set( *bombManager.GetBombObject(i) );
	}
}

void BlastManager::Maintain(const BombManager &bombManager)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->Maintain();
	}
}

void BlastManager::CheckHitObject(MapObstacle *mapObstacle)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->CheckHitObject(mapObstacle);
	}
}

void BlastManager::CheckHitCharactor(Charactor *charactor)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->CheckHitCharactor(charactor);
	}
}

void BlastManager::CheckHitBomb(BombManager *bombManager)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		for(int j=0,sizebomb=bombManager->vbomb->size(); j<sizebomb; ++j)
		{
			blast[i]->CheckHitBomb(bombManager->GetBombObject(j));
		}
	}
}

void BlastManager::CheckHitItem(ItemManager *itemManager)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		for(int j=0; j<ITEMNUM; ++j)
		{
			blast[i]->CheckHitItem(itemManager->GetItemInstance(j));
		}
	}
}

void BlastManager::CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager)
{
	for(int i=0,size=blast.size(); i<size; ++i)
	{
		blast[i]->CheckHit(mapobstacle1, mapobstacle2, charactor, bombManager,itemManager);
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




