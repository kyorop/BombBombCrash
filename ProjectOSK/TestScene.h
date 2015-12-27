#pragma once
#include "Scene_Base.h"
#include "Player.h"

namespace BombBombCrash
{
	class ControlPassingCollision;
	class Drawing;

	class TestScene:public Scene_Base
	{
		std::shared_ptr<Player> player;
		std::shared_ptr<Drawing> drawer;
		std::shared_ptr<GameManager> gameManager;
		std::shared_ptr<ControlPassingCollision> passingCollision;
	public:
		void Draw() override;

		void Initialize() override;
		void Finalize() override;
	private:
		void UpdateScene() override;
	public:
		void Update() override;
		TestScene();
		~TestScene();
	};

	
}
