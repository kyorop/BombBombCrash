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
	class GameManager:public ISceneProgress, public Task
	{
		std::shared_ptr<Player> player;
		std::shared_ptr<Drawing> drawer;
		std::shared_ptr<ControlPassingCollision> passingCollision;
		std::shared_ptr<Timer> timer;
		std::shared_ptr<GameEffect> gameEffect;

		std::shared_ptr<GameObjectManager> gameObjects;

		void GenerateObjects();
	public:
		GameManager();

		void Initialize() override;

		void Update() override;
		
		void Draw() override;

		void Finalize() override;
	};
}


