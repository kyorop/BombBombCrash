#include "Scene_Menu.h"
#include "ISceneChanger.h"
#include "Scene_Game.h"
#include "SecretCommand.h"

Scene_Menu::Scene_Menu()
	:command(new SecretCommand()),
	titleFontHandle(CreateFontToHandle(NULL, 60, 2))
{
}


Scene_Menu::~Scene_Menu(void)
{
	delete command;
	DeleteFontToHandle(titleFontHandle);
}


void Scene_Menu::UpdateScene()
{
	if(CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		sceneMrg->ChangeScene(ISceneChanger::SCENE_ROUND);
	}
}

void Scene_Menu::Update(void)
{
	//シーン更新
	UpdateScene();
	command->CheckHitSecretCommand();
}


void Scene_Menu::Draw(void)
{
	int white = GetColor(255,255,255);
	int red = GetColor(176, 48, 96);
	DrawStringToHandle(170, 150, "BOMB BOMB CRASH", white, titleFontHandle);
	DrawString(280,450,"PUSH ENTER KEY TO START", white);
}