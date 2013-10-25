#include "Collision.h"
#include "ICollisionable.h"
#include "PlayerBomb.h"
#include "EnemyBomb.h"
#include "MapObstacle.h"
#include "DxLib.h"
#include <typeinfo>

Collision::Collision(void)
	:disableGoingThrough(),
	bomb(),
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

//void Collision::RegisterWithBomb(ICollisionable *pBomb)
//{
//	bomb.push_back(pBomb);
//}
//
//void Collision::RegisterWithCharactor(ICollisionable *pCharacter)
//{
//	character.push_back(pCharacter);
//}

void Collision::Register(ICollisionable *anythingCollisionable)
{
	if( typeid(anythingCollisionable) == typeid(PlayerBomb) || typeid(anythingCollisionable) == typeid(EnemyBomb) )
	{
		disableGoingThrough.push_back(anythingCollisionable);
	}
	else if(typeid(anythingCollisionable) == typeid(MapObstacle))
	{
		disableGoingThrough.push_back(anythingCollisionable);
	}
}

void Collision::CheckCollision()
{
	for (int ic = 0,sizeChara=character.size(); ic < sizeChara; ++ic)
	{
		for (int ib = 0,sizeBomb=disableGoingThrough.size(); ib < sizeBomb; ib++)
		{
			// ©
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);//“r’†
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);//ã‚¢‚Á‚½
	
			//¨ 
			if((disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()- 32);//“r’†
			if((disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit <=character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX() - 32);//ã‚¢‚Á‚½

			// 
			//ª
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());//¶s‚­
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());//‰Es‚­

			//«
			// 
			if( (disableGoingThrough[ib]->GetY()< character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY()-32);//¶s‚­
			if( (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag()== TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY()-32);//‰Es‚­

			//^¶
			if( (disableGoingThrough[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && disableGoingThrough[ib]->GetFlag() == TRUE )character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);

			//^‰E
			if( (disableGoingThrough[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX()- 32);
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() - 32);

			//^ã
			if( (disableGoingThrough[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());

			//^‰º
			if( (disableGoingThrough[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY() - 32);
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY() - 32);

			//•Ç‚Ì¶ãŠp
			if( (disableGoingThrough[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+haba) && (disableGoingThrough[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetY()+haba) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//•Ç‚Ì‰EãŠp
			if( (disableGoingThrough[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetY()+haba) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
			//•Ç‚Ì¶‰ºŠp
			if( (disableGoingThrough[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+haba) && (disableGoingThrough[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//•Ç‚Ì‰E‰ºŠp
			if( (disableGoingThrough[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && (disableGoingThrough[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
	
		}
	}
}


