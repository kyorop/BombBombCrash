#include "BombSetManager.h"
#include "Bomb.h"

BombSetManager::BombSetManager(void)
	:num_upFireLevel(0)
{
	bombs.push_back(std::make_unique<Bomb>());
}


BombSetManager::~BombSetManager(void)
{
}


void BombSetManager::Set(int x, int y)
{
	for(int i = 0, size = bombs.size(); i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			bombs[i]->Set(x, y);
			if(i != j)
			{
				if (bombs[j]->GetFlag() 
					&& bombs[j]->GetX() == bombs[i]->GetX() 
					&& bombs[j]->GetY() == bombs[i]->GetY())
				{
					bombs[j]->SetFlag(false);
				}
			}
		}
	}
}


void BombSetManager::Update(void)
{
	for (auto& bomb : bombs)
	{
		bomb->Update();
	}
}


void BombSetManager::Draw(void)
{
	for (auto& bomb:bombs)
	{
		bomb->Draw();
	}
}


void BombSetManager::UpNum(void)
{
	auto newBomb = std::make_unique<Bomb>();

	//‘¼‚Ì‰Î—Í‚Æ“¯‚¶‚É‚·‚é
	for (int i = 0; i < num_upFireLevel; ++i)
		newBomb->UpFireLevel();

	bombs.push_back(move(newBomb));
}


void BombSetManager::UpFireLevel(void)
{
	for (auto& bomb:bombs)
	{
		bomb->UpFireLevel();
	}
	++num_upFireLevel;
}


void BombSetManager::CheckBombOverlap(void)
{
}
