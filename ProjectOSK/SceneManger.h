#pragma once
#include "ISceneChanger.h"

class Scene_Base;
class SceneManger
	:public ISceneChanger
{
private:
	Scene_Base *scene;
public:
	SceneManger(void);
	~SceneManger(void);

	void Update(void);
	void Draw(void);
	void ChangeScene(Scene_Base *nextScene) override;
};

