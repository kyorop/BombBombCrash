#include "Scene_Round.h"
#include "Timer.h"
#include "DxLib.h"

int Scene_Round::roundNum = 1;

Scene_Round::Scene_Round(void)
	:timer(new Timer)
{
}


Scene_Round::~Scene_Round(void)
{
	delete timer;
}


void Scene_Round::UpdateScene()
{
	if(timer->CountDownRealTime(2*1000))
	{
		sceneMrg->ChangeScene(ISceneChanger::SCENE_GAME);
	}
}


void Scene_Round::Finalize()
{
	++roundNum;
}


void Scene_Round::Update()
{
	UpdateScene();
}


void Scene_Round::Draw()
{
	int black = GetColor(255,255,255);
	DrawFormatString(400-50, 300-7, black,"Round  %d",roundNum);
}


void Scene_Round::ResetRound()
{
	roundNum = 1;
}