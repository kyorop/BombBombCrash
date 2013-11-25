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
	CharacterSet* player2;
	std::vector<CharacterSet*> enemy;
	Timer* timer;
	Timer* winTimer;
	Timer* loseTimer;
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


//**------------------------------------------------------------

class BombSetManager;
class GameEffect
{
private:
	int image_bombLevel;
	int image_fireLevel;
	const int white;
	const int x;
	const int y;
	BombSetManager* bomb;
public:
	GameEffect(void);
	~GameEffect(void);

	void SetBomb();
	void Update();
	void DrawGameEffect();
	void DrawMenuEffect();
};