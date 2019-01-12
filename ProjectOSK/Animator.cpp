#include "Animator.h"

void Animator::Play(const int x, const int y)
{
	position_.X = x;
	position_.Y = y;
	Play();
}

void Animator::Play(const ln::Vector2& position)
{
	position_ = position;
	Play();
}
