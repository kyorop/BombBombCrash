#pragma once
#include "ISceneProgress.h"

namespace BombBombCrash
{
	interface IGameProgress;

	class GameManager:public ISceneProgress
	{
		std::list<std::shared_ptr<IGameProgress>> gameElements;
	public:
		void Initialize() override;

		void Update() override;
		
		void Draw() override;
		
		void Destroy() override;
		
		void AddElement(const std::shared_ptr<IGameProgress>& element);
	};
}


