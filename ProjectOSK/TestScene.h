#pragma once
#include "Scene_Base.h"

namespace BombBombCrash
{
	class GameManager;
	class TestScene:public Scene_Base
	{
		std::shared_ptr<GameManager> gameManager;
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
