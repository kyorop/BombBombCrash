#include "BombSetManager.h"
#include "Bomb.h"

BombController::BombController(void)
	:num_upFireLevel(0)
{
	bombs.push_back(std::make_unique<Bomb>());
}


BombController::~BombController(void)
{
}


void BombController::Set(int x, int y)
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


void BombController::Update(void)
{
	for (auto& bomb : bombs)
	{
		bomb->Update();
	}
}


void BombController::Draw(void)
{
	for (auto& bomb:bombs)
	{
		bomb->Draw();
	}
}


void BombController::Increment(void)
{
	auto newBomb = std::make_unique<Bomb>();

	//‘¼‚Ì‰Î—Í‚Æ“¯‚¶‚É‚·‚é
	for (int i = 0; i < num_upFireLevel; ++i)
		newBomb->UpFireLevel();

	bombs.push_back(move(newBomb));
}


void BombController::IncrementFirepower(void)
{
	for (auto& bomb:bombs)
	{
		bomb->UpFireLevel();
	}
	++num_upFireLevel;
}

int BombController::BombSize() const
{
	return bombs.size();
}

int BombController::Firepower()
{
	if (bombs.empty())
		return 0;

	return bombs[0]->GetFireLevel();
}
