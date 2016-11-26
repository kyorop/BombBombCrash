#include "GameObjectManager.h"
#include "IGameProgress.h"

using namespace BombBombCrash;

GameObjectManager::GameObjectManager(GameManager* gameManager): gameElements(),
                                                                addedElements(),
                                                                gameManager(gameManager)
{
}

void GameObjectManager::Initialize()
{
	for (auto& element : addedElements)
		element->Initialize(*gameManager);

	gameElements = addedElements;
	addedElements.clear();
}

void GameObjectManager::Update()
{
	if (!addedElements.empty())
	{
		for (auto& newElement : addedElements)
			newElement->Initialize(*gameManager);
		gameElements.insert(end(gameElements), begin(addedElements), end(addedElements));
		addedElements.clear();
	}

	auto killedItr = remove_if(begin(gameElements), end(gameElements), [](const std::shared_ptr<IGameProgress>& object)
	{
		return object->CanRemove();
	});
	gameElements.erase(killedItr, end(gameElements));

	for (auto& element : gameElements)
		element->Update(*gameManager);
}

void GameObjectManager::Draw()
{
	for (auto& element : gameElements)
		element->Draw(*gameManager);
}

void GameObjectManager::Finalize()
{
	for (auto& element : gameElements)
		element->Destroy(*gameManager);
}

void GameObjectManager::AddElement(const std::shared_ptr<IGameProgress>& element)
{
	if (element == nullptr)
		return;
	addedElements.push_back(element);
}
