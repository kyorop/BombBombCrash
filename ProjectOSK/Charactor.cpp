#include "Charactor.h"

namespace BombBombCrash
{

	Character::Character(const ln::Vector2& position, int width, int height):
		MapObject(position , width , height), speed(1), fireLevel(1), bombNum(1)
	{
	}
}


