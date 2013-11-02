#pragma once

class Scene_Base;
class ISceneChanger
{
public:
	virtual ~ISceneChanger(void){};
	virtual void ChangeScene(Scene_Base *nextScene) = 0;
};

