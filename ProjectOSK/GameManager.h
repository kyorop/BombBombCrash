#pragma once
#include "ISceneProgress.h"
#include "Task.h"

namespace BombBombCrash
{
	interface IGameProgress;
	class ControlPassingCollision;
	class Drawing;
	class GameEffect;
	class Timer;
	class Player;
	class GameObjectManager;
	class CollisionManager;
	class GameManager:public Task
	{
		std::shared_ptr<Player> player;
		std::shared_ptr<Drawing> drawer;
		std::shared_ptr<Timer> timer;
		std::shared_ptr<GameEffect> gameEffect;

		std::shared_ptr<GameObjectManager> gameObjects;
		std::shared_ptr<CollisionManager> collisionMng;
		void GenerateObjects();
	public:
		GameManager();

		void Initialize() override;

		void Update() override;
		
		void Draw() override;

		void Finalize() override;
	};
}


