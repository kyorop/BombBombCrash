#pragma once
#include "MapObject.h"
#include "AnimationClip.h"
#include "Image.h"

class HardBlock:public BombBombCrash::MapObject
{
	AnimationClip block_image_;
public:

	HardBlock(ln::Vector2 initial_position) 
	:MapObject(initial_position),
	block_image_(BombBombCrash::Image::GetInstance()->Load("Images\\rimblock.bmp"))
	{}
	
	ObjectType Type() const override{ return ObjectType::HardBlock; }
	
	void Initialize() override;
	
	void Update() override;
	
	void Draw() override;
	
	void Finalize() override;
};
