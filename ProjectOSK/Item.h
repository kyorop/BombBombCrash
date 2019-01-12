#pragma once
#include "MapObject.h"
#include "AnimationClip.h"

namespace BombBombCrash
{
	class Item:public MapObject
	{
		AnimationClip image_;
		const ObjectType item_type_;
	public:
		Item(AnimationClip image, ObjectType item_type) :
			MapObject(ln::Vector2(0,0)),
			image_(std::move(image)),
			item_type_(item_type)
		{
		}

		void Draw() override;
		ObjectType Type() const override{ return item_type_; }
		void OnCollide(MapObject& other) override;
	};
}




