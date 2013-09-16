#include "EnemyBombManager.h"
#include "Enemy.h"
#include "EnemyBomb.h"

EnemyBombManager::EnemyBombManager(void)
{
	(*vbomb)[0] = new EnemyBomb;
}

void EnemyBombManager::AddBomb(const Charactor &charactor)
{
	if(charactor.GetBombNum() > nowBombNum)//�V���Ƀ{���A�C�e�����l��������A�{�����𑝂₷
	{
		vbomb->push_back(new EnemyBomb);
		++this->nowBombNum;
	}
}

void EnemyBombManager::BombSet(const Enemy &enemy)
{
	for(int i=0, size=vbomb->size(); i<size; ++i)
	{
		(*vbomb)[i]->BombSet(enemy);
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

EnemyBombManager::~EnemyBombManager(void)
{
}
