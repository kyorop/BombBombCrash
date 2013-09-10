#include "BombManager.h"
#include "Bomb.h"
#include "ItemManager.h"
#include "Player.h"
#include "DxLib.h"
#define BOMB 1

BombManager::BombManager(void):
	vbomb(new std::vector<Bomb*>(1)), nowBombNum(1)
{
	(*vbomb)[0] = new Bomb;
}

void BombManager::AddBomb(const Charactor &charactor)
{
	if(charactor.GetBombNum() > nowBombNum)//新たにボムアイテムを獲得したら、ボム数を増やす
	{
		vbomb->push_back(new Bomb);
		++this->nowBombNum;
	}
}

void BombManager::BombSet(const Charactor &charactor)
{
	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		(*vbomb)[i]->BombSet(charactor);
		for(int j=0,size=vbomb->size(); j<size; ++j)
		{
			if(i != j)
			{
				(*vbomb)[i]->CheckBombOverlap(*(*vbomb)[j]);
			}
		}
		//else
		//	continue;
		//if((*vbomb)[i]->GetFlag() == true)
		//	break;
	}
}

void BombManager::MaintainBomb()
{
	//if(key.CheckOnePushKey(KEY_INPUT_SPACE))
	{
		for(int i=0, size=vbomb->size(); i<size; ++i)
		{
			//if((*vbomb)[i]->GetFlag()==TRUE)
			//{
				(*vbomb)[i]->MaintainBomb();
				//if((*vbomb)[i]->GetFlag()==FALSE)
					//break;
			//}
		}
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
	
	int num=0;
	for(int i=0, size=vbomb->size(); i<size; ++i) 
	{
		if((*vbomb)[i]->GetFlag()==1)
			++num;
	}
	return num;
	//return this->nowBombNum;
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

Bomb* BombManager::GetBombObject(int index)const
{
	return (*this->vbomb)[index];
}