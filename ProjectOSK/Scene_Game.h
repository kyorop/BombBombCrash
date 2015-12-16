#pragma once
#include "Scene_Base.h"
#include <vector>
#include "IDrawable.h"


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
		std::shared_ptr<Player> player;
		std::vector<Character*> enemy;
		std::shared_ptr<Timer> timer;
		std::shared_ptr<Timer> winTimer;
		std::shared_ptr<Timer> loseTimer;
		std::shared_ptr<GameEffect> gameEffect;
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


class BombController;

namespace BombBombCrash
{
	class GameEffect:public IDrawable
	{
	private:
		int image_bombLevel;
		int image_fireLevel;
		const int white;
		const int x;
		const int y;
		BombController* bomb;
		std::shared_ptr<Timer> timer;


	public:
		explicit GameEffect(const std::shared_ptr<Timer>& timer);
		~GameEffect(void);

		void Update();
		void DrawGameEffect();
		void DrawMenuEffect();
		void Draw() override;
	};
}
