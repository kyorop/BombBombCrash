#include "SceneManger.h"
#include "Scene_Base.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"

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
		scene->Finalize();		//���̃V�[���ɕς��O�ɍ��̃V�[���̏�����
		delete scene;

		switch(nextScene)
		{
		case ISceneChanger::SCENE_MENU:
			scene  = new Scene_Menu;
			break;
		case ISceneChanger::SCENE_GAME:
			scene = new Scene_Game;
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