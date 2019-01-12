#include "stdafx.h"
#include "BombAnimation.h"
#include "Image.h"

using namespace BombBombCrash;

AnimationClip BombAnimation::bomb_animation_clip_;

BombAnimation::BombAnimation()
{
	bomb_animation_clip_ = Image::GetInstance()->Load("Images\\bomb.png", 60, 6, 10, 32, 32);
}

void BombAnimation::Play()
{
	const int animpat = ((GetNowCount() & INT_MAX) / (1000 / 12)) % 3;
	SetTransColor(255, 255, 255);
	DrawGraph(get_x(), get_y(), bomb_animation_clip_.get_handle(animpat), TRUE);
}
