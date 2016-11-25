#pragma once
#include "ISceneChanger.h"

namespace BombBombCrash
{
	class Drawing;
	class Scene_Base;
	class SceneManger:public ISceneChanger
	{
		int nextScene;
		std::shared_ptr<Scene_Base> scene;
		std::shared_ptr<Drawing> drawing;
	public:
		SceneManger(void);
		~SceneManger(void);

		void Update(void);
		void Draw(void);
		void ChangeScene(int nextScene) override;
	};

	
}


