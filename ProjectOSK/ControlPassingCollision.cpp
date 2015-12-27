#include "ControlPassingCollision.h"
#include "Charactor.h"
#include "Rect.h"
#include "CollisionUtil.h"

using namespace BombBombCrash;

std::vector<std::shared_ptr<MapObject>> ControlPassingCollision::notPassables;
std::vector<std::shared_ptr<Character>> ControlPassingCollision::movers;

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
//	for (int ic = 0, sizeChara = mover.size(); ic < sizeChara; ++ic)
//	{
//		for (int ib = 0, size = notPassables.size(); ib < size; ib++)
//		{
//			if ((notPassables[ib]->RX() - degreeOfHit <= mover[ic]->X() && mover[ic]->X() <= notPassables[ib]->RX()) && (notPassables[ib]->Y() + degreeOfHit <= mover[ic]->Y() && mover[ic]->Y() < notPassables[ib]->DY() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->X() + 32);//�r��
//			if ((notPassables[ib]->RX() - degreeOfHit <= mover[ic]->X() && mover[ic]->X() <= notPassables[ib]->RX()) && (notPassables[ib]->Y() + degreeOfHit <= mover[ic]->DY() && mover[ic]->DY() < notPassables[ib]->DY() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->X() + 32);//�ア����
//
//			if ((notPassables[ib]->X() <= mover[ic]->RX() && mover[ic]->RX() <= notPassables[ib]->X() + degreeOfHit) && (notPassables[ib]->Y() + degreeOfHit <= mover[ic]->Y() && mover[ic]->Y() <= notPassables[ib]->DY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->X() - 32);//�r��
//			if ((notPassables[ib]->X() <= mover[ic]->RX() && mover[ic]->RX() <= notPassables[ib]->X() + degreeOfHit) && (notPassables[ib]->Y() + degreeOfHit <= mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->DY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->X() - 32);//�ア����
//
//			if ((notPassables[ib]->DY() - degreeOfHit < mover[ic]->Y() && mover[ic]->Y() <= notPassables[ib]->DY()) && (notPassables[ib]->X() + degreeOfHit <= mover[ic]->X() && mover[ic]->X() < notPassables[ib]->RX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->DY());//���s��
//			if ((notPassables[ib]->DY() - degreeOfHit < mover[ic]->Y() && mover[ic]->Y() <= notPassables[ib]->DY()) && (notPassables[ib]->X() + degreeOfHit <= mover[ic]->RX() && mover[ic]->RX() < notPassables[ib]->RX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->DY());//�E�s��
//
//			if ((notPassables[ib]->Y()< mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->Y() + degreeOfHit) && (notPassables[ib]->X() + degreeOfHit <= mover[ic]->X() && mover[ic]->X() < notPassables[ib]->RX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->Y() - 32);//���s��
//			if ((notPassables[ib]->Y() < mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->Y() + degreeOfHit) && (notPassables[ib]->X() + degreeOfHit <= mover[ic]->RX() && mover[ic]->RX() < notPassables[ib]->RX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->Y() - 32);//�E�s��
//
//			if ((notPassables[ib]->Y() <= mover[ic]->Y() && mover[ic]->Y() < notPassables[ib]->Y() + degreeOfHit) && (notPassables[ib]->RX() - degreeOfHit < mover[ic]->X() && mover[ic]->X() <= notPassables[ib]->RX()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->X() + 32);
//			if ((notPassables[ib]->DY() - degreeOfHit <= mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->DY()) && (notPassables[ib]->RX() - degreeOfHit < mover[ic]->X() && mover[ic]->X() <= notPassables[ib]->RX()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->X() + 32);
//
//			if ((notPassables[ib]->Y() <= mover[ic]->Y() && mover[ic]->Y() < notPassables[ib]->Y() + degreeOfHit) && (notPassables[ib]->X() <= mover[ic]->RX() && mover[ic]->RX() < notPassables[ib]->X() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->X() - 32);
//			if ((notPassables[ib]->DY() - degreeOfHit <= mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->DY()) && (notPassables[ib]->X() <= mover[ic]->RX() && mover[ic]->RX() < notPassables[ib]->X() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->X() - 32);
//
//			if ((notPassables[ib]->X() <= mover[ic]->X() && mover[ic]->X() < notPassables[ib]->X() + degreeOfHit) && (notPassables[ib]->DY() - degreeOfHit < mover[ic]->Y() && mover[ic]->Y() <= notPassables[ib]->DY()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->DY());
//			if ((notPassables[ib]->RX() - degreeOfHit <= mover[ic]->RX() && mover[ic]->RX() <= notPassables[ib]->RX()) && (notPassables[ib]->DY() - degreeOfHit < mover[ic]->Y() && mover[ic]->Y() <= notPassables[ib]->DY()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->DY());
//
//			if ((notPassables[ib]->X() <= mover[ic]->X() && mover[ic]->X() < notPassables[ib]->X() + degreeOfHit) && (notPassables[ib]->Y() < mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->Y() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->Y() - 32);
//			if ((notPassables[ib]->RX() - degreeOfHit <= mover[ic]->RX() && mover[ic]->RX() <= notPassables[ib]->RX()) && (notPassables[ib]->Y() < mover[ic]->DY() && mover[ic]->DY() <= notPassables[ib]->Y() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->Y() - 32);
//
//			if ((notPassables[ib]->X() + degreeOfHit < mover[ic]->RX() && mover[ic]->RX() < notPassables[ib]->X() + haba) && (notPassables[ib]->Y() + degreeOfHit < mover[ic]->DY() && mover[ic]->DY() < notPassables[ib]->Y() + haba) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->X() - 32/*+degreeOfHit-character[ic]->GetMV()*/);
//			
//			if ((notPassables[ib]->RX() - haba < mover[ic]->X() && mover[ic]->X() < notPassables[ib]->RX() - degreeOfHit) && (notPassables[ib]->Y() + degreeOfHit < mover[ic]->DY() && mover[ic]->DY() < notPassables[ib]->Y() + haba) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->RX()/*-degreeOfHit+character[ic]->GetMV()*/);
//			
//			if ((notPassables[ib]->X() + degreeOfHit < mover[ic]->RX() && mover[ic]->RX() < notPassables[ib]->X() + haba) && (notPassables[ib]->DY() - haba < mover[ic]->Y() && mover[ic]->Y() < notPassables[ib]->DY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->X() - 32/*+degreeOfHit-character[ic]->GetMV()*/);
//			
//			if ((notPassables[ib]->RX() - haba < mover[ic]->X() && mover[ic]->X() < notPassables[ib]->RX() - degreeOfHit) && (notPassables[ib]->DY() - haba < mover[ic]->Y() && mover[ic]->Y() < notPassables[ib]->DY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->RX()/*-degreeOfHit+character[ic]->GetMV()*/);
//
//		}
//	}

	for (auto& wall : notPassables)
	{
		for (auto& mover: movers)
		{
			float wallW = wall->Width();
			float wallH = wall->Height();
			ln::Vector2 wallPos = wall->Position();
			ln::Vector2 wallLowerRightPos = wall->LowerRightPosition();

			ln::Vector2 upperPading(padding, 0);
			ln::Vector2 lowerPadding(-padding, - (wallH - padding));
			Rect upperBlock(wallPos + upperPading, wallLowerRightPos + lowerPadding);
			DrawBox(upperBlock.Left(), upperBlock.Top(), upperBlock.Right(), upperBlock.Bottom(), GetColor(255, 0, 0), true);
			if (Collision::Test(mover->Rect(), upperBlock))
				mover->Translate(ln::Vector2(0, -(mover->DY() - upperBlock.Top())));


			ln::Vector2 leftPaddingForUpper(0, padding);
			ln::Vector2 leftPaddingForLower(-(wallW-padding), -padding);
			Rect leftBlock(wallPos + leftPaddingForUpper, wallLowerRightPos + leftPaddingForLower);
			DrawBox(leftBlock.Left(), leftBlock.Top(), leftBlock.Right(), leftBlock.Bottom(), GetColor(255, 0, 0), true);
			if (Collision::Test(mover->Rect(), leftBlock))
				mover->Translate(ln::Vector2(-(mover->X() - wallPos.X + mover->Width()), 0));

			ln::Vector2 bottomPaddingForUpper(padding, wallH-padding);
			ln::Vector2 bottomPaddingForLower(-padding, 0);
			Rect bottomBlock(wallPos + bottomPaddingForUpper, wallLowerRightPos + bottomPaddingForLower);
			DrawBox(bottomBlock.Left(), bottomBlock.Top(), bottomBlock.Right(), bottomBlock.Bottom(), GetColor(255, 0, 0), true);
			if (Collision::Test(mover->Rect(), bottomBlock))
				mover->Translate(ln::Vector2(0, wallLowerRightPos.Y - mover->Y()));

			ln::Vector2 rightPaddingForUpper(wallW-padding, padding);
			ln::Vector2 rightPaddingForLower(0, -padding);
			Rect rightBlock(wallPos + rightPaddingForUpper, wallLowerRightPos + rightPaddingForLower);
			DrawBox(rightBlock.Left(), rightBlock.Top(), rightBlock.Right(), rightBlock.Bottom(), GetColor(255, 0, 0), true);
			if (Collision::Test(mover->Rect(), rightBlock))
				mover->Translate(ln::Vector2(wallLowerRightPos.X - mover->X(), 0));
		}
	}
}
