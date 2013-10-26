#include "Collision.h"
#include "ICollisionable.h"
#include "PlayerBomb.h"
#include "EnemyBomb.h"
#include "MapObstacle.h"
#include "Player.h"
#include "MapObject.h"
#include "Map.h"
#include "DxLib.h"
#include "Explosion.h"
#include <typeinfo.h>

Collision::Collision(void)
	:disableGoingThrough(),
	bomb(),
	character(),
	softBlock(),
	hardBlock(),
	map(),
	fire()
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

void Collision::Register(ICollisionable *anythingCollisionable)
{
	const type_info &type = typeid( *anythingCollisionable );

	if( type == typeid(Player) )
	{
		character.push_back(anythingCollisionable);
	}
	else if( type  == typeid(PlayerBomb) || typeid(anythingCollisionable) == typeid(EnemyBomb) )
	{
		disableGoingThrough.push_back(anythingCollisionable);
	}
	else if( type == typeid(MapObstacle) )
	{
		MapObstacle *map = dynamic_cast<MapObstacle*>(anythingCollisionable);
		if(map->GetId() == Map::HARDBLOCK)
		{
			hardBlock.push_back(anythingCollisionable);
			disableGoingThrough.push_back(anythingCollisionable);
		}
		else if(map->GetId() == Map::SOFTBLOCK)
		{
			softBlock.push_back(anythingCollisionable);
		}
	}
}

void Collision::RegisterWithFire(Explosion *fire)
{
	this->fire.push_back(fire);
}

void Collision::CheckEnableToPass()
{
	for (int ic = 0,sizeChara=character.size(); ic < sizeChara; ++ic)
	{
		for (int ib = 0,size=disableGoingThrough.size(); ib < size; ib++)
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

void Collision::CheckCollisionWithFire()
{
	std::list<Explosion*>::iterator itrFire;
	std::list<ICollisionable*>::iterator itrHardBlock;
	
	for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
	{
		int x_fire = (*itrFire)->GetX();
		int y_fire = (*itrFire)->GetY();
		int rx_fire = (*itrFire)->GetRX();
		int dy_fire = (*itrFire)->GetDY();

		for (itrHardBlock = hardBlock.begin(); itrHardBlock != hardBlock.end(); ++itrHardBlock)
		{
			int x_hblock = (*itrHardBlock)->GetX();
			int y_hblock = (*itrHardBlock)->GetY();
			int rx_hblock = (*itrHardBlock)->GetRX();
			int dy_hblock = (*itrHardBlock)->GetDY();

			if((*itrFire)->GetExplosion() == 1)
			{
				if(x_hblock+degreeOfHit < rx_fire && x_fire < rx_hblock-degreeOfHit && y_hblock+degreeOfHit < dy_fire && y_fire < dy_hblock-degreeOfHit)
				{
					(*itrFire)->SetExplosion(0);
				}
			}
		}
		
	}
}

void Collision::CheckCollision()
{
	CheckEnableToPass();
	CheckCollisionWithFire();
}
