#include "BombManager.h"
#include "Bomb.h"
#include "ItemManager.h"
#include "Player.h"
#define BOMB 1

BombManager::BombManager(void):
	vbomb(new std::vector<Bomb*>(1)), nowBombNum(0)
{
	(*vbomb)[0] = new Bomb;
}

void BombManager::AddBomb(const ItemManager &itemManager)
{
	if(itemManager.GetBombState() > nowBombNum)//新たにボムアイテムを獲得したら、ボム数を増やす
	{
		vbomb->push_back(new Bomb);
		++nowBombNum;
	}
	
	//if(manageItem.CheckHitCharactor(player) == BOMB)
	//static int count;
	//if(count == 0)
	//{
	//	vbomb->push_back(new Bomb);
	//	count = 1;
	//}
	
	//if(itemManager.CheckHitCharactor(player) == BOMB)
	//{
	//	vbomb->push_back(new Bomb);
	//}
}

void BombManager::BombSet(const Charactor &charactor)
{
	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		if( (*vbomb)[i]->GetFlag() == 0 )
		{
			(*vbomb)[i]->BombSet(charactor);
		}
		else
			continue;
		if((*vbomb)[i]->GetFlag() == 1)
			break;
	}
	//for(int i=vbomb->size()-1, size=vbomb->size(); i>=0; --i)
	//{
	//	(*vbomb)[i]->BombSet(charactor);
	//}
}

void BombManager::MaintainBomb()
{
	for(int i=0, size=vbomb->size(); i<size; ++i)
	//for(int i=vbomb->size()-1, size=vbomb->size(); i>=0; --i)
	{
		(*vbomb)[i]->MaintainBomb();
	}
}

void BombManager::Draw()
{
	this->size = vbomb->size();
	for(int i=0, size=vbomb->size(); i<size; ++i) 
	{
		(*vbomb)[i]->Draw();
	}
}

int BombManager::GetBombNum()
{
	/*
	int num=0;
	for(int i=0, size=vbomb->size(); i<size; ++i) 
	{
		if((*vbomb)[i]->GetFlag()==1)
			++num;
	}
	*/
	return this->nowBombNum;
}

BombManager::~BombManager(void)
{
	std::vector<Bomb*>::iterator it = vbomb->begin();
	for(it; it != vbomb->end(); ++it)
	{
		delete *it;
	}
	delete vbomb;
}

int BombManager::GetBombFlag(int index)const
{
	return (*this->vbomb)[index]->GetFlag();
}

int BombManager::GetBombX(int index)const
{
	return (*this->vbomb)[index]->GetX();
}

int BombManager::GetBombY(int index)const
{
	return (*this->vbomb)[index]->GetY();
}
