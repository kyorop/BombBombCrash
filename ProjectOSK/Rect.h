#pragma once

namespace BombBombCrash
{
	class Rect
	{
	public:
		ln::Vector2 upperLeftPos;
		ln::Vector2 lowerRightPos;


		Rect(const ln::Vector2& upperLeftPos, const ln::Vector2& lowerRightPos)
			: upperLeftPos(upperLeftPos),
			  lowerRightPos(lowerRightPos)
		{
		}

		float Top() const;
		float Right() const;
		float Bottom() const;
		float Left() const;
	};
}



