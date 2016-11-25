#include "Scene_Base.h"

using namespace BombBombCrash;

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

