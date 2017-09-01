#pragma once
#include "Item.h"

namespace BombBombCrash
{
	class FireUpItem:public Item
	{
	public:
		FireUpItem(const ln::Vector2& position, int width, int height, int imageHandle);

		GameObjectType Type() const override;
	};
}



