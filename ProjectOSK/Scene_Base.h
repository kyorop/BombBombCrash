#pragma once
#include "ISceneChanger.h"
#include "Task.h"

namespace BombBombCrash
{
	struct ISceneProgress;

	class Scene_Base:public Task
	{
	protected:
		ISceneChanger *sceneMrg;
	private:
		virtual void UpdateScene() = 0;
	public:
		Scene_Base();
		virtual ~Scene_Base(void);

		void SetManager(ISceneChanger *sceneManager);
	};
}


