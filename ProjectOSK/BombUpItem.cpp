#include "BombUpItem.h"

BombBombCrash::BombUpItem::BombUpItem(const ln::Vector2& position, int width, int height, int imageHandle): Item(position, width, height, imageHandle)
{
}

BombBombCrash::MapObject::GameObjectType BombBombCrash::BombUpItem::Type() const
{
	return GameObjectType::BombUpItem;
}
