#include "GameObjectManager.h"

#include "MapObject.h"

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

	for (auto& element : gameElements)
		element->Update(*gameManager);

	auto killedItr = remove_if(begin(gameElements), end(gameElements), [](const std::shared_ptr<MapObject>& object)
	{
		return !object->Exists();
	});
	gameElements.erase(killedItr, end(gameElements));
}

void GameObjectManager::Draw()
{
	for (auto& element : gameElements)
		element->Draw(*gameManager);
}

void GameObjectManager::Finalize()
{
	for (auto& element : gameElements)
		element->Finalize(*gameManager);
}

void GameObjectManager::AddElement(const std::shared_ptr<MapObject>& element)
{
	if (element == nullptr)
		return;
	addedElements.push_back(element);
}
