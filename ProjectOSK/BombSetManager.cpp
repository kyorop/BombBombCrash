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
		bombSet[i]->Set(x, y);
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
