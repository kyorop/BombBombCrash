#include "CharacterKilledAnimation.h"
#include "Image.h"
#include "GameManager.h"

CharacterKilledAnimation::CharacterKilledAnimation(const ln::Vector2& killed_position)
	:killed_animation_(BombBombCrash::Image::GetInstance()->Load("Images\\bombman.png", 20, 4, 5, 32, 32)),
	killed_position_(killed_position)
{
}

void CharacterKilledAnimation::Initialize()
{
}

void CharacterKilledAnimation::Update()
{
	if (timer_.CountDownFrame(0.5 * 1000))
	{
		++anim_frame_;
		timer_.TurnReset();

		if (anim_frame_ == 3)
		{
			BombBombCrash::GameManager::Instance().DeleteTask(this);
		}
	}
}

void CharacterKilledAnimation::Draw()
{
	DrawGraph(killed_position_.X, killed_position_.Y, killed_animation_.get_handle(16+anim_frame_), true);
}

void CharacterKilledAnimation::Finalize()
{
}
