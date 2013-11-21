#include "SceneManger.h"
#include "Scene_Base.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"
#include "Scene_Round.h"
#include "Scene_Score.h"

SceneManger::SceneManger(void)
	:nextScene(NOCHANGE),
	scene(new Scene_Menu)
{
	scene->SetManager(this);
	scene->Initialize();
}


SceneManger::~SceneManger(void)
{
	scene->Finalize();
	delete scene;
}


void SceneManger::Update(void)
{
	if(nextScene != NOCHANGE)
	{	
		scene->Finalize();		//次のシーンに変わる前に今のシーンの初期化
		delete scene;

		switch(nextScene)
		{
		case ISceneChanger::SCENE_MENU:
			scene  = new Scene_Menu;
			break;
		case ISceneChanger::SCENE_GAME:
			scene = new Scene_Game;
			break;
		case ISceneChanger::SCENE_ROUND:
			scene = new Scene_Round;
			break;
		case ISceneChanger::SCENE_SCORE:
			scene = new Scene_Score;
			break;
		}
		nextScene = ISceneChanger::NOCHANGE;
		scene->Initialize();
		scene->SetManager(this);
	}

	scene->Update();
}


void SceneManger::Draw(void)
{
	scene->Draw();
}


void SceneManger::ChangeScene(int next)
{
	nextScene = next;
}

void SceneManger::PlaySE(void)
{
	scene->PlaySE();
}
