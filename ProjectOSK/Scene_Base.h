#pragma once
#include "ISceneChanger.h"

namespace BombBombCrash
{
	struct ISceneProgress;

	class Scene_Base
	{
	protected:
		ISceneChanger *sceneMrg;
	private:
		virtual void UpdateScene() = 0;
	public:
		Scene_Base();
		virtual ~Scene_Base();

		void SetManager(ISceneChanger *sceneManager);

		virtual void Initialize(){}
		virtual void Update(){}
		virtual void Draw(){}
		virtual void Finalize(){}
	};
}


