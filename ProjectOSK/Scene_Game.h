#pragma once
#include "Scene_Base.h"
#include <vector>


class GameField;
class CharacterSet;
class Timer;
class GameEffect;
class Scene_Game
	:public Scene_Base
{
private:
	GameField *gameScreen;
	CharacterSet *player;
	CharacterSet *enemy;
	CharacterSet *enemy2;
	CharacterSet *enemy3;
	CharacterSet *enemy4;
	Timer* timer;
	GameEffect* gameEffect;
private:
	void UpdateScene() override;
public:
	Scene_Game();
	~Scene_Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void PlaySE() override;
};

