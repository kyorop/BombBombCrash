#pragma once
#include "Scene_Base.h"
#include <vector>


namespace BombBombCrash
{
	class Map;
	class Player;
	class Timer;
	class Character;
	class GameField;
	class GameEffect;
	class Drawing;

	class Scene_Game:public Scene_Base
	{
	private:
		GameField *gameScreen;
		std::shared_ptr<Player> player;
		std::vector<Character*> enemy;
		Timer* timer;
		Timer* winTimer;
		Timer* loseTimer;
		GameEffect* gameEffect;
		std::shared_ptr<Drawing> graphics;
		std::shared_ptr<Map> map;

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
}


//**------------------------------------------------------------

class BombController;

namespace BombBombCrash
{
	class GameEffect
	{
	private:
		int image_bombLevel;
		int image_fireLevel;
		const int white;
		const int x;
		const int y;
		BombController* bomb;
	public:
		GameEffect(void);
		~GameEffect(void);

		void SetBomb();
		void Update();
		void DrawGameEffect();
		void DrawMenuEffect();
	};
}
