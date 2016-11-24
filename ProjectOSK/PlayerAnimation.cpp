#include "PlayerAnimation.h"
#include "Image.h"
#include "Charactor.h"
#include "Player.h"
#include "Timer.h"

using namespace BombBombCrash;

PlayerAnimation::PlayerAnimation(const Player& player):
player(player),
image_left(Image::GetInstance()->GetCharacterImage(player.Id(), Image::LEFT)),
image_right(Image::GetInstance()->GetCharacterImage(player.Id(), Image::RIGHT)),
image_up(Image::GetInstance()->GetCharacterImage(player.Id(), Image::UP)),
image_down(Image::GetInstance()->GetCharacterImage(player.Id(), Image::DOWN)),
image_death(Image::GetInstance()->GetCharacterImage(player.Id(), Image::DEATH)),
animpat(0),
deathAnimTimer(new Timer()),
deathAnimFrame(0),
killedPos()
{
	deathAnimTimer->TurnReset();
}

void PlayerAnimation::Walk()
{
	int image = 0;
	animpat = ((GetNowCount() & INT_MAX) / (1000 / 12)) % 4;
	{
		if (player.IsWalking())
		{
			int muki = player.Direction();
			if (muki == player.LEFT)
				image = image_left[animpat];
			else if (muki == player.RIGHT)
				image = image_right[animpat];
			else if (muki == player.UP)
				image = image_up[animpat];
			else if (muki == player.DOWN)
				image = image_down[animpat];
		}
		else
		{
			animpat = 0;
			int muki = player.Direction();
			if (muki == player.LEFT)
				image = image_left[animpat];
			else if (muki == player.RIGHT)
				image = image_right[animpat];
			else if (muki == player.UP)
				image = image_up[animpat];
			else if (muki == player.DOWN)
				image = image_down[animpat];
		}
	}

	auto pos = player.Position();
	DrawGraph(pos.X, pos.Y, image, TRUE);
}

void PlayerAnimation::Killed()
{
	if (deathAnimTimer->CountDownFrame(1 * 1000))
	{
		if (deathAnimFrame == 0)
			killedPos = player.Position();
		++deathAnimFrame;
		if (deathAnimFrame == 3)
		{
			deathAnimTimer->TurnReset();
			deathAnimFrame = 0;
		}
	}

	DrawGraph(killedPos.X, killedPos.Y, image_death[deathAnimFrame], true);
}
