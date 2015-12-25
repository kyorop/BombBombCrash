#include "ControlPassingCollision.h"
#include "Charactor.h"

using namespace BombBombCrash;

std::vector<std::shared_ptr<MapObject>> ControlPassingCollision::notPassables;

ControlPassingCollision::ControlPassingCollision()
{
}


ControlPassingCollision::~ControlPassingCollision()
{
}

void ControlPassingCollision::Add(const std::shared_ptr<Character>& movingObject)
{
	mover.push_back(movingObject);
}

void ControlPassingCollision::Add(const std::shared_ptr<MapObject>& notPassable)
{
	notPassables.push_back(notPassable);
}

void ControlPassingCollision::Update()
{
	for (int ic = 0, sizeChara = mover.size(); ic < sizeChara; ++ic)
	{
		for (int ib = 0, size = notPassables.size(); ib < size; ib++)
		{
			if ((notPassables[ib]->GetRX() - degreeOfHit <= mover[ic]->GetX() && mover[ic]->GetX() <= notPassables[ib]->GetRX()) && (notPassables[ib]->GetY() + degreeOfHit <= mover[ic]->GetY() && mover[ic]->GetY() < notPassables[ib]->GetDY() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->GetX() + 32);//�r��
			if ((notPassables[ib]->GetRX() - degreeOfHit <= mover[ic]->GetX() && mover[ic]->GetX() <= notPassables[ib]->GetRX()) && (notPassables[ib]->GetY() + degreeOfHit <= mover[ic]->GetDY() && mover[ic]->GetDY() < notPassables[ib]->GetDY() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->GetX() + 32);//�ア����

			if ((notPassables[ib]->GetX() <= mover[ic]->GetRX() && mover[ic]->GetRX() <= notPassables[ib]->GetX() + degreeOfHit) && (notPassables[ib]->GetY() + degreeOfHit <= mover[ic]->GetY() && mover[ic]->GetY() <= notPassables[ib]->GetDY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->GetX() - 32);//�r��
			if ((notPassables[ib]->GetX() <= mover[ic]->GetRX() && mover[ic]->GetRX() <= notPassables[ib]->GetX() + degreeOfHit) && (notPassables[ib]->GetY() + degreeOfHit <= mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetDY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->GetX() - 32);//�ア����

			if ((notPassables[ib]->GetDY() - degreeOfHit < mover[ic]->GetY() && mover[ic]->GetY() <= notPassables[ib]->GetDY()) && (notPassables[ib]->GetX() + degreeOfHit <= mover[ic]->GetX() && mover[ic]->GetX() < notPassables[ib]->GetRX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetDY());//���s��
			if ((notPassables[ib]->GetDY() - degreeOfHit < mover[ic]->GetY() && mover[ic]->GetY() <= notPassables[ib]->GetDY()) && (notPassables[ib]->GetX() + degreeOfHit <= mover[ic]->GetRX() && mover[ic]->GetRX() < notPassables[ib]->GetRX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetDY());//�E�s��

			if ((notPassables[ib]->GetY()< mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetY() + degreeOfHit) && (notPassables[ib]->GetX() + degreeOfHit <= mover[ic]->GetX() && mover[ic]->GetX() < notPassables[ib]->GetRX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetY() - 32);//���s��
			if ((notPassables[ib]->GetY() < mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetY() + degreeOfHit) && (notPassables[ib]->GetX() + degreeOfHit <= mover[ic]->GetRX() && mover[ic]->GetRX() < notPassables[ib]->GetRX() - degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetY() - 32);//�E�s��

			if ((notPassables[ib]->GetY() <= mover[ic]->GetY() && mover[ic]->GetY() < notPassables[ib]->GetY() + degreeOfHit) && (notPassables[ib]->GetRX() - degreeOfHit < mover[ic]->GetX() && mover[ic]->GetX() <= notPassables[ib]->GetRX()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->GetX() + 32);
			if ((notPassables[ib]->GetDY() - degreeOfHit <= mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetDY()) && (notPassables[ib]->GetRX() - degreeOfHit < mover[ic]->GetX() && mover[ic]->GetX() <= notPassables[ib]->GetRX()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->GetX() + 32);

			if ((notPassables[ib]->GetY() <= mover[ic]->GetY() && mover[ic]->GetY() < notPassables[ib]->GetY() + degreeOfHit) && (notPassables[ib]->GetX() <= mover[ic]->GetRX() && mover[ic]->GetRX() < notPassables[ib]->GetX() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->GetX() - 32);
			if ((notPassables[ib]->GetDY() - degreeOfHit <= mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetDY()) && (notPassables[ib]->GetX() <= mover[ic]->GetRX() && mover[ic]->GetRX() < notPassables[ib]->GetX() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetX(notPassables[ib]->GetX() - 32);

			if ((notPassables[ib]->GetX() <= mover[ic]->GetX() && mover[ic]->GetX() < notPassables[ib]->GetX() + degreeOfHit) && (notPassables[ib]->GetDY() - degreeOfHit < mover[ic]->GetY() && mover[ic]->GetY() <= notPassables[ib]->GetDY()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetDY());
			if ((notPassables[ib]->GetRX() - degreeOfHit <= mover[ic]->GetRX() && mover[ic]->GetRX() <= notPassables[ib]->GetRX()) && (notPassables[ib]->GetDY() - degreeOfHit < mover[ic]->GetY() && mover[ic]->GetY() <= notPassables[ib]->GetDY()) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetDY());

			if ((notPassables[ib]->GetX() <= mover[ic]->GetX() && mover[ic]->GetX() < notPassables[ib]->GetX() + degreeOfHit) && (notPassables[ib]->GetY() < mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetY() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetY() - 32);
			if ((notPassables[ib]->GetRX() - degreeOfHit <= mover[ic]->GetRX() && mover[ic]->GetRX() <= notPassables[ib]->GetRX()) && (notPassables[ib]->GetY() < mover[ic]->GetDY() && mover[ic]->GetDY() <= notPassables[ib]->GetY() + degreeOfHit) && notPassables[ib]->Exists() == TRUE)mover[ic]->SetY(notPassables[ib]->GetY() - 32);

			if ((notPassables[ib]->GetX() + degreeOfHit < mover[ic]->GetRX() && mover[ic]->GetRX() < notPassables[ib]->GetX() + haba) && (notPassables[ib]->GetY() + degreeOfHit < mover[ic]->GetDY() && mover[ic]->GetDY() < notPassables[ib]->GetY() + haba) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->GetX() - 32/*+degreeOfHit-character[ic]->GetMV()*/);
			
			if ((notPassables[ib]->GetRX() - haba < mover[ic]->GetX() && mover[ic]->GetX() < notPassables[ib]->GetRX() - degreeOfHit) && (notPassables[ib]->GetY() + degreeOfHit < mover[ic]->GetDY() && mover[ic]->GetDY() < notPassables[ib]->GetY() + haba) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
			
			if ((notPassables[ib]->GetX() + degreeOfHit < mover[ic]->GetRX() && mover[ic]->GetRX() < notPassables[ib]->GetX() + haba) && (notPassables[ib]->GetDY() - haba < mover[ic]->GetY() && mover[ic]->GetY() < notPassables[ib]->GetDY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->GetX() - 32/*+degreeOfHit-character[ic]->GetMV()*/);
			
			if ((notPassables[ib]->GetRX() - haba < mover[ic]->GetX() && mover[ic]->GetX() < notPassables[ib]->GetRX() - degreeOfHit) && (notPassables[ib]->GetDY() - haba < mover[ic]->GetY() && mover[ic]->GetY() < notPassables[ib]->GetDY() - degreeOfHit) && notPassables[ib]->Exists() == 1)mover[ic]->SetX(notPassables[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);

		}
	}
}
