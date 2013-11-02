#pragma once
#include "Scene_Base.h"

class ISceneChanger;
class Scene_Menu
	:public Scene_Base
{
private:
	void UpdateScene() override;
public:
	Scene_Menu();
	~Scene_Menu(void);

	void Update(void) override;
	void Draw(void) override;
};

