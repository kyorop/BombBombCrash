#include "SceneManger.h"
#include "Scene_Base.h"
#include "Scene_Menu.h"
#include "Scene_Game.h"

SceneManger::SceneManger(void)
	:scene(new Scene_Menu)
{
	scene->SetManager(this);
}


SceneManger::~SceneManger(void)
{
}


void SceneManger::Update(void)
{
	scene->Update();
}


void SceneManger::Draw(void)
{
	scene->Draw();
}


void SceneManger::ChangeScene(Scene_Base *nextScene)
{
	delete scene;
	scene = nextScene;
	scene->SetManager(this);
}