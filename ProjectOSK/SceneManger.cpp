#include "SceneManger.h"
#include "Scene_Base.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"
#include "Scene_Round.h"
#include "Scene_Score.h"
#include "Drawing.h"
#include "TestScene.h"

using namespace BombBombCrash;

SceneManger::SceneManger(void):
nextScene(NOCHANGE),
scene()
{
	scene = std::make_shared<TestScene>();
	Drawing::Add(scene);
	scene->SetManager(this);
	scene->Initialize();
}


SceneManger::~SceneManger(void)
{
	scene->Finalize();
}


void SceneManger::Update(void)
{
	if(nextScene != NOCHANGE)
	{	
		scene->Finalize();		//次のシーンに変わる前に今のシーンの初期化

		switch(nextScene)
		{
		case SCENE_MENU:
			scene = std::make_shared<Scene_Menu>();
			break;
		case SCENE_GAME:
			scene = std::make_shared<Scene_Game>();
			break;
		case SCENE_ROUND:
			scene = std::make_shared<Scene_Round>();
			break;
		case SCENE_SCORE:
			scene = std::make_shared<Scene_Score>();
			break;
		}
		Drawing::Add(scene);
		nextScene = NOCHANGE;
		scene->Initialize();
		scene->SetManager(this);
	}

	scene->Update();
}


void SceneManger::Draw(void)
{
	drawing->Update();
}


void SceneManger::ChangeScene(int next)
{
	nextScene = next;
}
