#pragma once
#include "Item.h"

namespace BombBombCrash
{
	class BombUpItem:public Item
	{
	public:
		BombUpItem(const ln::Vector2& position, int width, int height, int imageHandle);

	public:
		GameObjectType Type() const override;
	};
}



