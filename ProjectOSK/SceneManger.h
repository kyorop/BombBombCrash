#pragma once
#include "ISceneChanger.h"

namespace BombBombCrash
{
	class Drawing;
	class Scene_Base;
	class SceneManger:public ISceneChanger
	{
		int nextScene;
		std::unique_ptr<Scene_Base> scene;
	public:
		SceneManger();
		virtual ~SceneManger();

		virtual void Update();
		virtual void Draw();
		void ChangeScene(int nextScene) override;
	};

	
}


