#pragma once
#include "MapObject.h"
#include "AnimationClip.h"

class BreakableBlock:public BombBombCrash::MapObject
{
	AnimationClip image_;
	std::unique_ptr<MapObject> item_;
public:
	BreakableBlock(ln::Vector2 initial_position):
	MapObject(initial_position),
	item_(nullptr)
	{
	}

	BreakableBlock(ln::Vector2 position, std::unique_ptr<MapObject> item) :
		MapObject(position),
		item_(move(item))
	{
	}

	ObjectType Type() const override{ return BREAKABLE_BLOCK; }
	
	void OnCollide(MapObject& other) override;
	
	void Initialize() override;
	
	void Draw() override;

	void SetItem(std::unique_ptr<MapObject> item){ item_ = move(item); }
};
