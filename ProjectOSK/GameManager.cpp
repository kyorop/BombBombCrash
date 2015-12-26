#include "GameManager.h"
#include "IGameProgress.h"

void BombBombCrash::GameManager::AddElement(const std::shared_ptr<IGameProgress>& element)
{
	if (element == nullptr)
		return;
	addedElements.push_back(element);
}

void BombBombCrash::GameManager::Initialize()
{
	for (auto& element : addedElements)
		element->Initialize(*this);

	gameElements = addedElements;
	addedElements.clear();
}

void BombBombCrash::GameManager::Update()
{
	if (!addedElements.empty())
	{
		for (auto& newElement : addedElements)
			newElement->Initialize(*this);
		gameElements.insert(end(gameElements), begin(addedElements), end(addedElements));
		addedElements.clear();
	}

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
