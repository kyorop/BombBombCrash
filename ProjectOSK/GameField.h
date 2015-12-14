#pragma once

class Map;
class Block;
class ItemManager;

namespace BombBombCrash
{
	class GameField
	{
	public:
		GameField(void);
		~GameField(void);
		void Initialize();
		void Update();
		void Draw();
	};
}

