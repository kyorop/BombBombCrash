#include "BombManager.h"
#include "PlayerBomb.h"
#include "ItemManager.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#define BOMB 1

BombManager::BombManager(void):
	vbomb(new std::vector<Bomb*>(1)), nowBombNum(1)
{
	(*vbomb)[0] = new PlayerBomb;
}

void BombManager::AddBomb(const Charactor &charactor)
{
	if(charactor.GetBombNum() > nowBombNum)//新たにボムアイテムを獲得したら、ボム数を増やす
	{
		vbomb->push_back(new PlayerBomb);
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
				//(*vbomb)[i]->CheckBombOverlap(*(*vbomb)[j]);
				(*vbomb)[j]->CheckBombOverlap(*(*vbomb)[i]);
			}
		}
		//else
		//	continue;
		//if((*vbomb)[i]->GetFlag() == true)
		//	break;
	}
}

void BombManager::CheckHit(Charactor *charactor)
{
	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		(*vbomb)[i]->CheckHit(charactor);
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



void BombManager::Register(const Charactor &chara)
{
	/*for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		if((*vbomb)[i]->GetFlag() == 0)
			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 0);
	}
	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		if((*vbomb)[i]->GetFlag() == 1)
			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 1);
	}*/

	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		if((*vbomb)[i]->GetFlag() == 0)
		{
			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 0, FALSE);
			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 0, TRUE);
			//MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 0, 1, );
			//MapState::GetInstance()->SetDanger((*vbomb)[i]->GetY()/32,(*vbomb)[i]->GetX()/32, chara.GetFireLevel(), 0);
		}
		else if((*vbomb)[i]->GetFlag() == 1)
		{
			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 1, FALSE);
			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), chara.GetFireLevel(), TRUE);
			//MapState::GetInstance()->SetDanger((*vbomb)[i]->GetY()/32,(*vbomb)[i]->GetX()/32, chara.GetFireLevel(), 1);
		}
	}
}
