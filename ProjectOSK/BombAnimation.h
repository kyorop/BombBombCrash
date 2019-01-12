#pragma once
#include "AnimationClip.h"
#include "Animator.h"

class BombAnimation:public Animator
{
	static AnimationClip bomb_animation_clip_;
public:
	BombAnimation();
	void Play() override;
};
