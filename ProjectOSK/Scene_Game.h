#pragma once
#include "Scene_Base.h"
#include <vector>

//class ISceneChanger;
class GameField;
class CharacterSet;
class Timer;
class Scene_Game
	:public Scene_Base
{
private:
	GameField *gameScreen;
	CharacterSet *player;
	std::vector<CharacterSet*> enemy;
	Timer* timer;
private:
	void UpdateScene() override;
public:
	Scene_Game();
	~Scene_Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};

