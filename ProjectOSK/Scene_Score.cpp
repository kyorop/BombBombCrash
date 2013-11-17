#include "Scene_Score.h"
#include "Timer.h"
#include "DxLib.h"

int Scene_Score::winNum;
int Scene_Score::loseNum;

Scene_Score::Scene_Score(void)
	:timer(new Timer)
{
}


Scene_Score::~Scene_Score(void)
{
	delete timer;
}


void Scene_Score::UpdateScene()
{
	if(timer->CountDown(3*1000))
		sceneMrg->ChangeScene(ISceneChanger::SCENE_ROUND);
}


void Scene_Score::Initialize()
{
	if(winNum > win_max || loseNum > lose_max)
	{
		winNum = 0;
		loseNum = 0;
	}
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