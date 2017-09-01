#pragma once
#include "Item.h"

namespace BombBombCrash
{
	class SpeedUpItem:public Item
	{
		public:
		SpeedUpItem(const ln::Vector2& position, int width, int height, int imageHandle);

	public:
		GameObjectType Type() const override;
	};
}



