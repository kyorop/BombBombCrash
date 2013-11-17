#pragma once
#include "Scene_Base.h"

class Timer;
class Scene_Score
	:public Scene_Base
{
private:
	Timer* timer;
	static int winNum;
	static int loseNum;
	static const int win_max = 2;
	static const int lose_max = 2;
private:
	void UpdateScene()override;
public:
	Scene_Score(void);
	~Scene_Score(void);

	void Initialize()override;
	void Update()override;
	void Draw()override;

	static void IncrementWin(){++winNum;}
	static void IncrementLose(){++loseNum;}
};

