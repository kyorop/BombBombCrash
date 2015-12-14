#pragma once
#include "ISceneChanger.h"

namespace BombBombCrash
{
	class Scene_Base
	{
	protected:
		ISceneChanger *sceneMrg;
	private:
		virtual void UpdateScene() = 0;
	public:
		Scene_Base();
		virtual ~Scene_Base(void);

		void SetManager(ISceneChanger *sceneManager);
		virtual void Initialize(){}
		virtual void Update(void) = 0;
		virtual void Draw(void) = 0;
		virtual void Finalize(){}
		virtual void PlaySE(){};
	};

	
}


