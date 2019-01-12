#include "PlayerWalkingAnimation.h"
#include "Image.h"

using namespace BombBombCrash;

PlayerWalkingAnimation::PlayerWalkingAnimation(IPlayerInput& input) 
: player_input_(input),
walking_animation_(Image::GetInstance()->Load("Images\\bombman.png", 20, 4, 5, 32, 32)),
direction_(0)
{
}

void PlayerWalkingAnimation::Play()
{
	int animpat = ((GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
	const int pre_direction = direction_;
	if (player_input_.GetInputMoveUp())
	{
		direction_ = 0;
	}
	else if (player_input_.GetInputMoveDown())
	{
		direction_ = 4;
	}
	else if (player_input_.GetInputMoveLeft())
	{
		direction_ = 8;
	}
	else if (player_input_.GetInputMoveRight())
	{
		direction_ = 12;
	}
	else
	{
		direction_ = pre_direction;
		animpat = 0;
	}

	DrawGraph(get_x(), get_y(), walking_animation_.get_handle(direction_ + animpat), TRUE);
}


