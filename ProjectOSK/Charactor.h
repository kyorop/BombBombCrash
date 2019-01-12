#pragma once
#include "MapObject.h"

namespace BombBombCrash
{
	class Character:public MapObject
	{
	public:
		enum Direction
		{
			LEFT,
			RIGHT,
			UP,
			DOWN,
		};
	private:
		int speed;
		int fireLevel;
		int bombNum;

	public:

		Character(const ln::Vector2& position, int width, int height);

		int Speed(){ return speed; }
		int BombSize(){ return bombNum; }
		int FireLevel(){ return fireLevel; }

		void IncrementSpeed(){ ++speed; }
		void IncrementBomb(){ ++bombNum; }
		void IncrementFireLevel(){ ++fireLevel; }
	};
}




