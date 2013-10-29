#include "BombSetManager.h"
#include "BombSet.h"

BombSetManager::BombSetManager(void)
	:bombSet(0),
	num_upFireLevel(0)
{
	bombSet.push_back(new BombSet);
}


BombSetManager::~BombSetManager(void)
{
}


void BombSetManager::Set(int x, int y)
{
	for(int i = 0, size = bombSet.size(); i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			bombSet[i]->Set(x, y);
			if(i != j)
			{
				if(bombSet[j]->GetFlag() == 1 && bombSet[j]->GetBombX() == bombSet[i]->GetBombX() && bombSet[j]->GetBombY() == bombSet[i]->GetBombY())
				{
					bombSet[j]->SetFlag(0);
				}
			}
		}
	}
}


void BombSetManager::Update(void)
{
	for(int i = 0, size = bombSet.size(); i < size; ++i)
	{
		bombSet[i]->Update();
	}
}


void BombSetManager::Draw(void)
{
	for(int i = 0, size = bombSet.size(); i < size; ++i)
	{
		bombSet[i]->Draw();
	}
}


void BombSetManager::UpNum(void)
{
	BombSet *pBombSet = new BombSet;
	//‘¼‚Ì‰Î—Í‚Æ“¯‚¶‚É‚·‚é
	for (int i = 0; i < num_upFireLevel; ++i)
		pBombSet->UpFireLevel();		
	bombSet.push_back(pBombSet);
}


void BombSetManager::UpFireLevel(void)
{
	for(int i = 0, size = bombSet.size(); i < size; ++i)
	{
		bombSet[i]->UpFireLevel();
	}
	++num_upFireLevel;
}


void BombSetManager::CheckBombOverlap(void)
{
}
