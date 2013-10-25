#include "Collision.h"
#include "ICollisionable.h"
#include "DxLib.h"

Collision::Collision(void)
	:bomb(),
	character(),
	block(),
	map()
{
}

Collision::~Collision(void)
{
}

Collision* Collision::GetInstance()
{
	static Collision collision;
	return &collision;
}

void Collision::RegisterWithBomb(ICollisionable *pBomb)
{
	bomb.push_back(pBomb);
}

void Collision::RegisterWithCharactor(ICollisionable *pCharacter)
{
	character.push_back(pCharacter);
}

void Collision::CheckCollision()
{
	for (int ic = 0,sizeChara=character.size(); ic < sizeChara; ++ic)
	{
		for (int ib = 0,sizeBomb=bomb.size(); ib < sizeBomb; ib++)
		{
			//����
			if( (bomb[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= bomb[ib]->GetRX()) && (bomb[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() < bomb[ib]->GetDY()-degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetX(bomb[ib]->GetX() + 32);//�r��
			if( (bomb[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= bomb[ib]->GetRX()) && (bomb[ib]->GetY()+degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() < bomb[ib]->GetDY()-degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetX(bomb[ib]->GetX() + 32);//�ア����
	

			//����
			if((bomb[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= bomb[ib]->GetX()+degreeOfHit) && (bomb[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() <= bomb[ib]->GetDY()-degreeOfHit) && bomb[ib]->GetFlag() == 1)character[ic]->SetX(bomb[ib]->GetX()- 32);//�r��
			if((bomb[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= bomb[ib]->GetX()+degreeOfHit) && (bomb[ib]->GetY()+degreeOfHit <=character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetDY()-degreeOfHit) && bomb[ib]->GetFlag() == 1)character[ic]->SetX(bomb[ib]->GetX() - 32);//�ア����

					
			//��
			//��
			if( (bomb[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= bomb[ib]->GetDY()) && (bomb[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < bomb[ib]->GetRX()-degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetDY());//���s��
			if( (bomb[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= bomb[ib]->GetDY()) && (bomb[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < bomb[ib]->GetRX()-degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetDY());//�E�s��

			//��
			//��
			if( (bomb[ib]->GetY()< character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetY()+degreeOfHit) && (bomb[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < bomb[ib]->GetRX()-degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetY()-32);//���s��
			if( (bomb[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetY()+degreeOfHit) && (bomb[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < bomb[ib]->GetRX()-degreeOfHit) && bomb[ib]->GetFlag()== TRUE)character[ic]->SetY(bomb[ib]->GetY()-32);//�E�s��

			//�^��
			if( (bomb[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < bomb[ib]->GetY()+degreeOfHit) && (bomb[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= bomb[ib]->GetRX()) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetX(bomb[ib]->GetX() + 32);
			if( (bomb[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetDY()) && (bomb[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= bomb[ib]->GetRX()) && bomb[ib]->GetFlag() == TRUE )character[ic]->SetX(bomb[ib]->GetX() + 32);

			//�^�E
			if( (bomb[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < bomb[ib]->GetY()+degreeOfHit) && (bomb[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < bomb[ib]->GetX()+degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetX(bomb[ib]->GetX()- 32);
			if( (bomb[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetDY()) && (bomb[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < bomb[ib]->GetX()+degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetX(bomb[ib]->GetX() - 32);

			//�^��
			if( (bomb[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < bomb[ib]->GetX()+degreeOfHit) && (bomb[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= bomb[ib]->GetDY()) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetDY());
			if( (bomb[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= bomb[ib]->GetRX()) && (bomb[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= bomb[ib]->GetDY()) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetDY());

			//�^��
			if( (bomb[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < bomb[ib]->GetX()+degreeOfHit) && (bomb[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetY()+degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetY() - 32);
			if( (bomb[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= bomb[ib]->GetRX()) && (bomb[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= bomb[ib]->GetY()+degreeOfHit) && bomb[ib]->GetFlag() == TRUE)character[ic]->SetY(bomb[ib]->GetY() - 32);

			//�ǂ̍���p
			if( (bomb[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < bomb[ib]->GetX()+haba) && (bomb[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < bomb[ib]->GetY()+haba) && bomb[ib]->GetFlag() == 1)character[ic]->SetX(bomb[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//�ǂ̉E��p
			if( (bomb[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < bomb[ib]->GetRX()-degreeOfHit) && (bomb[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < bomb[ib]->GetY()+haba) && bomb[ib]->GetFlag() == 1)character[ic]->SetX(bomb[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
			//�ǂ̍����p
			if( (bomb[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < bomb[ib]->GetX()+haba) && (bomb[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < bomb[ib]->GetDY()-degreeOfHit) && bomb[ib]->GetFlag() == 1)character[ic]->SetX(bomb[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//�ǂ̉E���p
			if( (bomb[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < bomb[ib]->GetRX()-degreeOfHit) && (bomb[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < bomb[ib]->GetDY()-degreeOfHit) && bomb[ib]->GetFlag() == 1)character[ic]->SetX(bomb[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
	
		}
	}
}


