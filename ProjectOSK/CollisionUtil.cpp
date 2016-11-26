#include "CollisionUtil.h"
#include "Rect.h"

bool BombBombCrash::CollisionUtil::Test(const Rect& r1, const Rect& r2)
{
	if (r1.Left() < r2.Right() && r2.Left() < r1.Right()
		&& r1.Top() < r2.Bottom() && r2.Top() < r1.Bottom())
		return true;

	return false;
}
