#pragma once
#include "MapObject.h"

namespace BombBombCrash
{
	class CollisionableObject:public MapObject
	{
	public:
		explicit CollisionableObject(const ln::Vector2& position, int width, int height):
			MapObject(position, width, height)
		{}
		virtual void OnCollide(CollisionableObject* object)=0;
	};
}
