#pragma once
#include "Scene_Base.h"

class SecretCommand;
class ISceneChanger;
class Scene_Menu
	:public Scene_Base
{
private:
	const int pushEnter;
	SecretCommand* command;
private:
	void UpdateScene() override;
public:
	Scene_Menu();
	~Scene_Menu(void);

	void Update(void) override;
	void Draw(void) override;
};