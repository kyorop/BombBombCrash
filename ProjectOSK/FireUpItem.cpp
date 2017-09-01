#include "FireUpItem.h"

BombBombCrash::FireUpItem::FireUpItem(const ln::Vector2& position, int width, int height, int imageHandle): 
Item(position, width, height, imageHandle)
{
}

BombBombCrash::MapObject::GameObjectType BombBombCrash::FireUpItem::Type() const
{
	return GameObjectType::FireUpItem;
}
