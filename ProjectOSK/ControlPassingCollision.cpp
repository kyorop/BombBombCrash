#include "ControlPassingCollision.h"
#include "Charactor.h"
#include "Rect.h"
#include "CollisionUtil.h"

using namespace BombBombCrash;

std::list<std::shared_ptr<MapObject>> ControlPassingCollision::notPassables;
std::list<std::shared_ptr<Character>> ControlPassingCollision::movers;

ControlPassingCollision::ControlPassingCollision()
{
}

void ControlPassingCollision::Add(const std::shared_ptr<Character>& movingObject)
{
	movers.push_back(movingObject);
}

void ControlPassingCollision::Add(const std::shared_ptr<MapObject>& notPassable)
{
	notPassables.push_back(notPassable);
}

void ControlPassingCollision::Update()
{
	notPassables.remove_if([&](const std::shared_ptr<MapObject>& wall)
	{
		return !wall->Exists();
	});
	movers.remove_if([](const std::shared_ptr<Character>& mover)
	{
		return !mover->Exists();
	});

	for (auto& wall : notPassables)
	{
		for (auto& mover: movers)
		{
			float wallW = wall->Width();
			float wallH = wall->Height();
			auto wallPos = wall->Position();
			auto wallLowerRightPos = wall->LowerRightPosition();

			ln::Vector2 upperPading(padding, 0);
			ln::Vector2 lowerPadding(-padding, - (wallH - padding));
			Rect upperBlock(wallPos + upperPading, wallLowerRightPos + lowerPadding);
			if (Collision::Test(mover->Rect(), upperBlock))
				mover->Translate(ln::Vector2(0, -(mover->DY() - upperBlock.Top())));


			ln::Vector2 leftPaddingForUpper(0, padding);
			ln::Vector2 leftPaddingForLower(-(wallW-padding), -padding);
			Rect leftBlock(wallPos + leftPaddingForUpper, wallLowerRightPos + leftPaddingForLower);
			if (Collision::Test(mover->Rect(), leftBlock))
				mover->Translate(ln::Vector2(-(mover->X() - wallPos.X + mover->Width()), 0));

			ln::Vector2 bottomPaddingForUpper(padding, wallH-padding);
			ln::Vector2 bottomPaddingForLower(-padding, 0);
			Rect bottomBlock(wallPos + bottomPaddingForUpper, wallLowerRightPos + bottomPaddingForLower);
			if (Collision::Test(mover->Rect(), bottomBlock))
				mover->Translate(ln::Vector2(0, wallLowerRightPos.Y - mover->Y()));

			ln::Vector2 rightPaddingForUpper(wallW-padding, padding);
			ln::Vector2 rightPaddingForLower(0, -padding);
			Rect rightBlock(wallPos + rightPaddingForUpper, wallLowerRightPos + rightPaddingForLower);
			if (Collision::Test(mover->Rect(), rightBlock))
				mover->Translate(ln::Vector2(wallLowerRightPos.X - mover->X(), 0));
		}
	}
}
