#include "SpeedUpItem.h"

BombBombCrash::SpeedUpItem::SpeedUpItem(const ln::Vector2& position, int width, int height, int imageHandle):
Item(position, width, height, imageHandle)
{
}

BombBombCrash::MapObject::GameObjectType BombBombCrash::SpeedUpItem::Type() const
{
	return GameObjectType::SpeedUpItem;
}
