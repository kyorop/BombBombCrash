#include "SceneManger.h"
#include "Scene_Base.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"
#include "Scene_Round.h"
#include "Scene_Score.h"

using namespace BombBombCrash;

SceneManger::SceneManger(void):
nextScene(NOCHANGE),
scene(std::make_unique<Scene_Game>())
{
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
		scene->Finalize();		//���̃V�[���ɕς��O�ɍ��̃V�[���̏�����

		switch(nextScene)
		{
		case SCENE_MENU:
			scene = std::make_unique<Scene_Menu>();
			break;
		case SCENE_GAME:
			scene = std::make_unique<Scene_Game>();
			break;
		case SCENE_ROUND:
			scene = std::make_unique<Scene_Round>();
			break;
		case SCENE_SCORE:
			scene = std::make_unique<Scene_Score>();
			break;
		}
		nextScene = NOCHANGE;
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
