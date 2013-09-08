#include "BlastManager.h"
#include "ExplosionManager.h"
#include "BombManager.h"
#include "MapObstacle.h"
#include "Player.h"
#include "Charactor.h"
#include "ItemManager.h"
#include "Bomb.h"
#include "DxLib.h"


BlastManager::BlastManager(void):
	vblast(new std::vector<ExplosionManager*>(1))
{
	(*vblast)[0] = new ExplosionManager;
	this->nowBlastNum = 0;
}

void BlastManager::FireUp(const ItemManager &itemManager)
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->FireUp(itemManager);
	}
}

void BlastManager::Add(const ItemManager &manageItem)
{
	if(manageItem.GetBombState() > this->nowBlastNum)
	{
		vblast->push_back(new ExplosionManager);
		++this->nowBlastNum;
	}
}

void BlastManager::Set(const BombManager &bombManager)
{
	
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->Set(*bombManager.GetBombObject(i));
	}
}

void BlastManager::Maintain()
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->Maintain();
	}
}

void BlastManager::CheckHitObject(MapObstacle *mapObstacle)
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->CheckHitObject(mapObstacle);
	}
}

void BlastManager::CheckHitCharactor(Charactor *charactor)
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->CheckHitCharactor(charactor);
	}
}

void BlastManager::CheckHitBomb(BombManager *bombManager)
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		for(int j=0,sizebomb=bombManager->vbomb->size(); j<sizebomb; ++j)
		{
			(*vblast)[i]->CheckHitBomb(bombManager->GetBombObject(j));
		}
	}
}

void BlastManager::CheckHitItem(ItemManager *itemManager)
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		for(int j=0; j<ITEMNUM; ++j)
		{
			(*vblast)[i]->CheckHitItem(itemManager->GetItemInstance(j));
		}
	}
}

void BlastManager::CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager)
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->CheckHit(mapobstacle1, mapobstacle2, charactor, bombManager,itemManager);
	}
}

void BlastManager::Draw()
{
	for(int i=0,size=vblast->size(); i<size; ++i)
	{
		(*vblast)[i]->Draw();
	}
}


BlastManager::~BlastManager(void)
{
	std::vector<ExplosionManager*>::iterator it = vblast->begin();
	for(it; it!=vblast->end(); ++it)
	{
		delete *it;
	}
	delete vblast;
}
