#pragma once
#include "ISceneChanger.h"
#include "Task.h"

namespace BombBombCrash
{
	class Drawing;
	class Scene_Base;
	class SceneManger:public ISceneChanger, public Task
	{
		int nextScene;
		std::shared_ptr<Scene_Base> scene;
	public:
		SceneManger(void);
		~SceneManger(void);

		void Update() override;
		void Draw() override;
		void ChangeScene(int nextScene) override;
	};

	
}


