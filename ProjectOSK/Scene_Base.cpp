#include "Scene_Base.h"


Scene_Base::Scene_Base()
	:sceneMrg()
{
}


Scene_Base::~Scene_Base(void)
{
}


void Scene_Base::SetManager(ISceneChanger *sceneManager)
{
	sceneMrg = sceneManager;
}