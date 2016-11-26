#pragma once
#include "Task.h"

namespace BombBombCrash
{
	interface IGameProgress;
	class GameManager;
	class MapObject;
	class GameObjectManager:public Task
	{
		std::list<std::shared_ptr<MapObject>> gameElements;
		std::list<std::shared_ptr<MapObject>> addedElements;
		GameManager* gameManager;
	public:

		explicit GameObjectManager(GameManager* gameManager);

		void Initialize() override;

		void Update() override;

		void Draw() override;

		void Finalize() override;

		void AddElement(const std::shared_ptr<MapObject>& element);
	};
}
