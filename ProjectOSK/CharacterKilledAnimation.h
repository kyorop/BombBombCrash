#pragma once
#include "AnimationClip.h"
#include "Timer.h"
#include "MapObject.h"

class CharacterKilledAnimation:public BombBombCrash::MapObject
{
	AnimationClip killed_animation_;
	ln::Vector2 killed_position_;
	BombBombCrash::Timer timer_;
	int anim_frame_;
public:
	CharacterKilledAnimation(const ln::Vector2& killed_position);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};
