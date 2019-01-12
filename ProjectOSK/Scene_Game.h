#pragma once
#include "Scene_Base.h"


namespace BombBombCrash
{
	class Scene_Game:public Scene_Base
	{	

		void UpdateScene() override;
	public:
		Scene_Game();
		~Scene_Game();

		void Initialize() override;
		void Finalize() override;
		void Update() override;
		void Draw() override;
	};
}
