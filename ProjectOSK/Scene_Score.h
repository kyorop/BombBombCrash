#pragma once
#include "Scene_Base.h"
#include "IDrawable.h"

namespace BombBombCrash
{
	class Timer;
	class Scene_Score:public Scene_Base
	{
		enum result
		{
			WIN,
			LOSE,
			NONE,
		};

		Timer* timer;
		static int winNum;
		static int loseNum;
		int hasIncremented;
		static result winOrLose;
		static const int win_max = 3;
		static const int lose_max = 3;
		int hasFinished;

		void UpdateScene()override;
	public:
		Scene_Score(void);
		~Scene_Score(void);

		void Finalize()override;
		void Update()override;
		void Draw() override;

		static void SetResult(result which){winOrLose = which;}
	};
}




