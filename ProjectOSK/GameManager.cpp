#include "GameManager.h"
#include "IGameProgress.h"

void BombBombCrash::GameManager::AddElement(const std::shared_ptr<IGameProgress>& element)
{
	if (element == nullptr)
		return;
	gameElements.push_back(element);
}

void BombBombCrash::GameManager::Initialize()
{
	for (auto& element : gameElements)
		element->Initialize(*this);
}

void BombBombCrash::GameManager::Update()
{
	auto killedItr = remove_if(begin(gameElements), end(gameElements), [](const std::shared_ptr<IGameProgress>& object)
	{
		return object->CanRemove();
	});
	gameElements.erase(killedItr, end(gameElements));

	for (auto& element : gameElements)
		element->Update(*this);
}

void BombBombCrash::GameManager::Draw()
{
	for (auto& element : gameElements)
		element->Draw(*this);
}

void BombBombCrash::GameManager::Destroy()
{
	for (auto& element : gameElements)
		element->Destroy(*this);
}
