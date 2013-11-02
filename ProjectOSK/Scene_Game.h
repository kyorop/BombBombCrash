#pragma once
#include "Scene_Base.h"
#include <vector>

//class ISceneChanger;
class GameField;
class CharacterSet;
class Scene_Game
	:public Scene_Base
{
private:
	GameField *const gameScreen;
	CharacterSet *const player;
	CharacterSet *const enemy;
	CharacterSet *const enemy2;
	CharacterSet *const enemy3;
	CharacterSet *const enemy4;
private:
	void UpdateScene() override;
public:
	Scene_Game();
	~Scene_Game();
	void Update() override;
	void Draw() override;
};

