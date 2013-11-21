#pragma once
#include "Scene_Base.h"

class Timer;
class Scene_Score
	:public Scene_Base
{
public:
	enum result
	{
		WIN,
		LOSE,
		NONE,
	};
private:
	Timer* timer;
	static int winNum;
	static int loseNum;
	int hasIncremented;
	static result winOrLose;
	static const int win_max = 3;
	static const int lose_max = 3;
private:
	void UpdateScene()override;
public:
	Scene_Score(void);
	~Scene_Score(void);

	void Finalize()override;
	void Update()override;
	void Draw()override;

	static void SetResult(result which){winOrLose = which;}
};

