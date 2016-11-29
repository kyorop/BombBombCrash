#include "Rect.h"

using namespace BombBombCrash;

float Rect::Top() const
{
	return upperLeftPos.Y;
}

float Rect::Right() const
{
	return lowerRightPos.X;
}

float Rect::Bottom() const
{
	return lowerRightPos.Y;
}

float Rect::Width() const
{
	return lowerRightPos.X - upperLeftPos.X;
}

float Rect::Height() const
{
	return lowerRightPos.Y - upperLeftPos.Y;
}

float Rect::Left() const
{
	return upperLeftPos.X;
}
