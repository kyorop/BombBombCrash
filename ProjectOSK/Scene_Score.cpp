#include "Scene_Score.h"
#include "Scene_Round.h"
#include "Timer.h"
#include "DxLib.h"

int Scene_Score::winNum;
int Scene_Score::loseNum;
Scene_Score::result Scene_Score::winOrLose = NONE;

Scene_Score::Scene_Score(void)
	:timer(new Timer),
	hasIncremented()
{
}


Scene_Score::~Scene_Score(void)
{
	delete timer;
}


void Scene_Score::UpdateScene()
{
	if(hasIncremented)
	{
		if(timer->CountDownFrame(2*1000))
		{
			if(winNum == win_max || loseNum == lose_max)
			{
				Scene_Round::ResetRound();
				sceneMrg->ChangeScene(ISceneChanger::SCENE_MENU);
			}
			else
				sceneMrg->ChangeScene(ISceneChanger::SCENE_ROUND);
		}
	}
	else
	{
		if(timer->CountDownRealTime(1*1000))
		{
			if(winOrLose == WIN)
				++winNum;
			else if(winOrLose == LOSE)
				++loseNum;

			hasIncremented = 1;
		}
	}
}


void Scene_Score::Finalize()
{
	if(winNum >= win_max || loseNum >= lose_max)
	{
		winNum = 0;
		loseNum = 0;
	}
	winOrLose = NONE;
}


void Scene_Score::Update()
{
	UpdateScene();
}


void Scene_Score::Draw()
{
	int white = GetColor(255,255,255);
	DrawFormatString(400-50, 300-7, white, "WIN    %d", winNum);
	DrawFormatString(400-50, 300-7+30, white, "LOSE   %d", loseNum);
}