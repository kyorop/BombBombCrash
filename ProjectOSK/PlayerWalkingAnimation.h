#pragma once
#include "Animator.h"
#include "AnimationClip.h"
#include "IPlayerInput.h"

namespace BombBombCrash
{
	class PlayerWalkingAnimation :public Animator
	{
		IPlayerInput& player_input_;
		AnimationClip walking_animation_;
		int direction_;
		void Play() override;
	public:

		explicit PlayerWalkingAnimation(IPlayerInput& input);
	};
}

