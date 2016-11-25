#pragma once
#include "Scene_Base.h"
#include <vector>
#include "IDrawable.h"


namespace BombBombCrash
{
	class ControlPassingCollision;
	class Map;
	class Player;
	class Timer;
	class Character;
	class GameField;
	class GameEffect;
	class Drawing;

	class Scene_Game:public Scene_Base
	{
		std::shared_ptr<Player> player;
		std::vector<Character*> enemy;
		std::shared_ptr<Timer> timer;
		std::shared_ptr<Timer> winTimer;
		std::shared_ptr<Timer> loseTimer;
		std::shared_ptr<GameEffect> gameEffect;
		std::shared_ptr<Drawing> graphics;
		std::shared_ptr<Map> map;
		
		std::shared_ptr<ControlPassingCollision> passingCollision;

		void UpdateScene() override;
	public:
		Scene_Game();
		~Scene_Game();

		void Initialize() override;
		void Finalize() override;
		void Update() override;
		void Draw() override;
	};
}
