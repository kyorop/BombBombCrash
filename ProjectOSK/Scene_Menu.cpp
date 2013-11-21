#include "Scene_Menu.h"
#include "ISceneChanger.h"
#include "Scene_Game.h"
#include "SecretCommand.h"
#include "DxLib.h"

Scene_Menu::Scene_Menu()
	:pushEnter(LoadGraph("pushenterkeytostart.png")),
	command(new SecretCommand())
{
}


Scene_Menu::~Scene_Menu(void)
{
	delete command;
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
	//�V�[���X�V
	UpdateScene();
	command->CheckHitSecretCommand();
}


void Scene_Menu::Draw(void)
{

	int deepskyblue = GetColor(0, 191, 255);
	//DrawFormatString(10, 10, deepskyblue,"�Q�[�����n�߂�ɂ̓G���^�[�L�[�������ĂˁI");
	DrawGraph(60, 450, pushEnter, true);
}