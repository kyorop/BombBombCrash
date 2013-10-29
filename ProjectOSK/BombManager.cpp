#include "BombManager.h"
#include "PlayerBomb.h"
#include "ItemManager.h"
#include "Player.h"
#include "MapState.h"
#include "Collision.h"
#include "DxLib.h"
#define BOMB 1

BombManager::BombManager(void):
	bomb(), 
	nowBombNum(1),
	bombImage()
{
	PlayerBomb * pbomb = new PlayerBomb;
	bomb.push_back(pbomb);
	Collision::GetInstance()->Register(pbomb);
	LoadDivGraph("bomb.png", 60, 6, 10, 32, 32, bombImage, FALSE);
}

void BombManager::Add()
{
	PlayerBomb * pbomb = new PlayerBomb;
	bomb.push_back(pbomb);
	Collision::GetInstance()->Register(pbomb);
	++this->nowBombNum;
}

void BombManager::BombSet(int x, int y)
{
	for(int i=0, size=bomb.size(); i<size; ++i)
	{
		bomb[i]->BombSet(x, y);
		for(int j=0,size=bomb.size(); j<size; ++j)
		{
			if( i != j )
			{
				bomb[j]->CheckBombOverlap(*bomb[i]);
			}
		}
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
		if(bomb[i]->GetFlag() == 1)
		{
			SetTransColor(255,255,255);
			DrawGraph(bomb[i]->GetX(), bomb[i]->GetY(), bombImage[0], FALSE);
		}
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