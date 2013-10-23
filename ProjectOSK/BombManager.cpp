#include "BombManager.h"
#include "PlayerBomb.h"
#include "ItemManager.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#define BOMB 1

BombManager::BombManager(void):
	bomb(), 
	nowBombNum(1)
{
	bomb.push_back(new PlayerBomb);
}

void BombManager::Add()
{
		bomb.push_back(new PlayerBomb);
		++this->nowBombNum;
}

void BombManager::BombSet(int x, int y)
{
	for(int i=0, size=bomb.size(); i<size; ++i)
	{
		bomb[i]->BombSet(charactor);
		for(int j=0,size=bomb.size(); j<size; ++j)
		{
			if(i != j)
			{
				//bomb[i]->CheckBombOverlap(*bomb[j]);
				bomb[j]->CheckBombOverlap(*bomb[i]);
			}
		}
		//else
		//	continue;
		//if(bomb[i]->GetFlag() == true)
		//	break;
	}
}

void BombManager::CheckHit(Charactor *charactor)
{
	for(int i=0, size=bomb.size(); i<size; ++i)
	{
		bomb[i]->CheckHit(charactor);
	}
}

void BombManager::MaintainBomb()
{
	//if(key.CheckOnePushKey(KEY_INPUT_SPACE))
	{
		for(int i=0, size=bomb.size(); i<size; ++i)
		{
			//if(bomb[i]->GetFlag()==TRUE)
			//{
				bomb[i]->MaintainBomb();
				//if(bomb[i]->GetFlag()==FALSE)
					//break;
			//}
		}
	}
}

void BombManager::Draw()
{
	this->size = bomb.size();
	for(int i=0, size=bomb.size(); i<size; ++i) 
	{
		bomb[i]->Draw();
	}
}

int BombManager::GetBombNum()
{
	
	int num=0;
	for(int i=0, size=bomb.size(); i<size; ++i) 
	{
		if(bomb[i]->GetFlag()==1)
			++num;
	}
	return num;
	//return this->nowBombNum;
}

BombManager::~BombManager(void)
{
	std::vector<Bomb*>::iterator it = bomb.begin();
	for(it; it != bomb.end(); ++it)
	{
		delete *it;
	}
}

int BombManager::GetFlag(int index)const
{
	return bomb[index]->GetFlag();
}

int BombManager::GetX(int index)const
{
	return bomb[index]->GetX();
}

int BombManager::GetY(int index)const
{
	return bomb[index]->GetY();
}

Bomb* BombManager::GetBombObject(int index)const
{
	return bomb[index];
}

int BombManager::GetAllBombNum()const
{
	return nowBombNum;
}

void BombManager::Register(const Charactor &chara)
{
	/*for(int i=0, size=bomb.size(); i<size; ++i)
	{
		if(bomb[i]->GetFlag() == 0)
			MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), 0);
	}
	for(int i=0, size=bomb.size(); i<size; ++i)
	{
		if(bomb[i]->GetFlag() == 1)
			MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), 1);
	}*/

	for(int i=0, size=bomb.size(); i<size; ++i)
	{
		if(bomb[i]->GetFlag() == 0)
		{
			MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), 0, FALSE);
			MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), 0, TRUE);
			//MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), 0, 1, );
			//MapState::GetInstance()->SetDanger(bomb[i]->GetY()/32,bomb[i]->GetX()/32, chara.GetFireLevel(), 0);
		}
		else if(bomb[i]->GetFlag() == 1)
		{
			MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), 1, FALSE);
			MapState::GetInstance()->SetBombState(bomb[i]->GetX(), bomb[i]->GetY(), chara.GetFireLevel(), TRUE);
			//MapState::GetInstance()->SetDanger(bomb[i]->GetY()/32,bomb[i]->GetX()/32, chara.GetFireLevel(), 1);
		}
	}
}
