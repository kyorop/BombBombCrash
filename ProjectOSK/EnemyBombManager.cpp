#include "EnemyBombManager.h"
#include "Enemy.h"
#include "EnemyBomb.h"
#include "MapState.h"

EnemyBombManager::EnemyBombManager(void)
{
	(*vbomb)[0] = new EnemyBomb;
}

void EnemyBombManager::AddBomb(const Charactor &charactor)
{
	if(charactor.GetBombNum() > nowBombNum)//新たにボムアイテムを獲得したら、ボム数を増やす
	{
		vbomb->push_back(new EnemyBomb);
		++this->nowBombNum;
	}
}

//void EnemyBombManager::BombSet(const Enemy &enemy)
//{
//	for(int i=0, size=vbomb->size(); i<size; ++i)
//	{
//		(*vbomb)[i]->BombSet(enemy);
//		for(int j=0,size=vbomb->size(); j<size; ++j)
//		{
//			if(i != j)
//			{
//				(*vbomb)[i]->CheckBombOverlap(*(*vbomb)[j]);
//			}
//		}
//		//else
//		//	continue;
//		//if((*vbomb)[i]->GetFlag() == true)
//		//	break;
//	}
//}

//void EnemyBombManager::Register(const Charactor &chara)
//{
//	for(int i=0, size=vbomb->size(); i<size; ++i)
//	{
//		if((*vbomb)[i]->GetFlag() == 0)
//		{
//			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 0);
//			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 0, 1);
//		}
//		else if((*vbomb)[i]->GetFlag() == 1)
//		{
//			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), 1);
//			MapState::GetInstance()->SetBombState((*vbomb)[i]->GetX(), (*vbomb)[i]->GetY(), chara.GetFireLevel(), 1);
//		}
//	}
//}

EnemyBombManager::~EnemyBombManager(void)
{
}
