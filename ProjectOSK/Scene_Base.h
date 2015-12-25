#pragma once
#include "ISceneChanger.h"
#include "IDrawable.h"

namespace BombBombCrash
{
	struct ISceneProgress;

	class Scene_Base: public IDrawable
	{
		std::vector<std::shared_ptr<ISceneProgress>> systems;
	protected:
		ISceneChanger *sceneMrg;
	private:
		virtual void UpdateScene() = 0;
	public:
		Scene_Base();
		virtual ~Scene_Base(void);

		void SetManager(ISceneChanger *sceneManager);
		void AddElement(std::shared_ptr<ISceneProgress> gameSystem);
		virtual void Initialize(){}
		virtual void Update(void) = 0;
		virtual void Finalize(){}
		virtual void PlaySE(){};
	};

	
}


