#pragma once
#include "ISceneChanger.h"
#include "IDrawable.h"

namespace BombBombCrash
{
	class Scene_Base: public IDrawable
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
		virtual void Finalize(){}
		virtual void PlaySE(){};
	};

	
}


