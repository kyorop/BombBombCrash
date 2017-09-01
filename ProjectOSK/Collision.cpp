#include "Collision.h"
#include "ICollisionable.h"
#include "Bomb.h"
#include "MapObstacle.h"
#include "Player.h"
#include "Enemy.h"
#include "MapObject.h"
#include "Item.h"
#include "Charactor.h"
#include "Block.h"


namespace BombBombCrash
{
	Collision::Collision(void)
		:disableGoingThrough(),
		 bomb(),
		 character(),
		 softBlock(),
		 hardBlock(),
		 map(),
		 fragile(),
		 item()
	{
	}


	Collision::~Collision(void)
	{
	}


	Collision* Collision::Instance()
	{
		static Collision collision;
		return &collision;
	}


	void Collision::Finalize()
	{
		disableGoingThrough.clear();
		bomb.clear();
		character.clear();
		softBlock.clear();
		hardBlock.clear();
		map.clear();
		fragile.clear();
		item.clear();
	}


	void Collision::Register(ICollisionable *anythingCollisionable)
	{
		const type_info &type = typeid( *anythingCollisionable );

		if( type == typeid(Player) || type == typeid(Enemy) )
		{
			character.push_back(anythingCollisionable);
			fragile.push_back(anythingCollisionable);
		}
		else if(type == typeid(Bomb))
		{
			disableGoingThrough.push_back(anythingCollisionable);
			fragile.push_back(anythingCollisionable);
		}
		else if( type == typeid(MapObstacle) )
		{
			MapObstacle *map = dynamic_cast<MapObstacle*>(anythingCollisionable);
			if(map->Type() == HARDBLOCK)
			{
				hardBlock.push_back(anythingCollisionable);
				disableGoingThrough.push_back(anythingCollisionable);
			}
			else if(map->Type() == SOFTBLOCK)
			{
				softBlock.push_back(anythingCollisionable);
				disableGoingThrough.push_back(anythingCollisionable);
				fragile.push_front(anythingCollisionable);
			}
		}
	}


	void Collision::RegisterWithItem(Item *pItem)
	{
		item.push_back(pItem);
		fragile.push_back(pItem);
	}


	void Collision::CheckEnableToPass()
	{
		for (int ic = 0,sizeChara=character.size(); ic < sizeChara; ++ic)
		{
			for (int ib = 0,size=disableGoingThrough.size(); ib < size; ib++)
			{
				//����
				if( (disableGoingThrough[ib]->RX()-degreeOfHit <= character[ic]->X() && character[ic]->X() <= disableGoingThrough[ib]->RX()) && (disableGoingThrough[ib]->Y()+degreeOfHit <= character[ic]->Y() && character[ic]->Y() < disableGoingThrough[ib]->DY()-degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->X() + 32);//�r��
				if( (disableGoingThrough[ib]->RX()-degreeOfHit <= character[ic]->X() && character[ic]->X() <= disableGoingThrough[ib]->RX()) && (disableGoingThrough[ib]->Y()+degreeOfHit <= character[ic]->DY() && character[ic]->DY() < disableGoingThrough[ib]->DY()-degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->X() + 32);//�ア����
	
				//����
				if((disableGoingThrough[ib]->X() <= character[ic]->RX() && character[ic]->RX() <= disableGoingThrough[ib]->X()+degreeOfHit) && (disableGoingThrough[ib]->Y()+degreeOfHit <= character[ic]->Y() && character[ic]->Y() <= disableGoingThrough[ib]->DY()-degreeOfHit) && disableGoingThrough[ib]->Exists() == 1)character[ic]->SetX(disableGoingThrough[ib]->X()- 32);//�r��
				if((disableGoingThrough[ib]->X() <= character[ic]->RX() && character[ic]->RX() <= disableGoingThrough[ib]->X()+degreeOfHit) && (disableGoingThrough[ib]->Y()+degreeOfHit <=character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->DY()-degreeOfHit) && disableGoingThrough[ib]->Exists() == 1)character[ic]->SetX(disableGoingThrough[ib]->X() - 32);//�ア����

				//��
				//��
				if( (disableGoingThrough[ib]->DY()-degreeOfHit < character[ic]->Y() && character[ic]->Y() <= disableGoingThrough[ib]->DY()) && (disableGoingThrough[ib]->X()+degreeOfHit <= character[ic]->X() && character[ic]->X() < disableGoingThrough[ib]->RX()-degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->DY());//���s��
				if( (disableGoingThrough[ib]->DY()-degreeOfHit < character[ic]->Y() && character[ic]->Y() <= disableGoingThrough[ib]->DY()) && (disableGoingThrough[ib]->X()+degreeOfHit <= character[ic]->RX() && character[ic]->RX() < disableGoingThrough[ib]->RX()-degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->DY());//�E�s��

				//��
				//��
				if( (disableGoingThrough[ib]->Y()< character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->Y()+degreeOfHit) && (disableGoingThrough[ib]->X()+degreeOfHit <= character[ic]->X() && character[ic]->X() < disableGoingThrough[ib]->RX()-degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->Y()-32);//���s��
				if( (disableGoingThrough[ib]->Y() < character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->Y()+degreeOfHit) && (disableGoingThrough[ib]->X()+degreeOfHit <= character[ic]->RX() && character[ic]->RX() < disableGoingThrough[ib]->RX()-degreeOfHit) && disableGoingThrough[ib]->Exists()== TRUE)character[ic]->SetY(disableGoingThrough[ib]->Y()-32);//�E�s��

				//�^��
				if( (disableGoingThrough[ib]->Y() <= character[ic]->Y() && character[ic]->Y() < disableGoingThrough[ib]->Y()+degreeOfHit) && (disableGoingThrough[ib]->RX()-degreeOfHit < character[ic]->X() && character[ic]->X() <= disableGoingThrough[ib]->RX()) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->X() + 32);
				if( (disableGoingThrough[ib]->DY()-degreeOfHit <= character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->DY()) && (disableGoingThrough[ib]->RX()-degreeOfHit < character[ic]->X() && character[ic]->X() <= disableGoingThrough[ib]->RX()) && disableGoingThrough[ib]->Exists() == TRUE )character[ic]->SetX(disableGoingThrough[ib]->X() + 32);

				//�^�E
				if( (disableGoingThrough[ib]->Y() <= character[ic]->Y() && character[ic]->Y() < disableGoingThrough[ib]->Y()+degreeOfHit) && (disableGoingThrough[ib]->X() <= character[ic]->RX() && character[ic]->RX() < disableGoingThrough[ib]->X()+degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->X()- 32);
				if( (disableGoingThrough[ib]->DY()-degreeOfHit <= character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->DY()) && (disableGoingThrough[ib]->X() <= character[ic]->RX() && character[ic]->RX() < disableGoingThrough[ib]->X()+degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->X() - 32);

				//�^��
				if( (disableGoingThrough[ib]->X() <= character[ic]->X() && character[ic]->X() < disableGoingThrough[ib]->X()+degreeOfHit) && (disableGoingThrough[ib]->DY()-degreeOfHit < character[ic]->Y() && character[ic]->Y() <= disableGoingThrough[ib]->DY()) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->DY());
				if( (disableGoingThrough[ib]->RX()-degreeOfHit <= character[ic]->RX() && character[ic]->RX() <= disableGoingThrough[ib]->RX()) && (disableGoingThrough[ib]->DY()-degreeOfHit < character[ic]->Y() && character[ic]->Y() <= disableGoingThrough[ib]->DY()) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->DY());

				//�^��
				if( (disableGoingThrough[ib]->X() <= character[ic]->X() && character[ic]->X() < disableGoingThrough[ib]->X()+degreeOfHit) && (disableGoingThrough[ib]->Y() < character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->Y()+degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->Y() - 32);
				if( (disableGoingThrough[ib]->RX()-degreeOfHit <= character[ic]->RX() && character[ic]->RX() <= disableGoingThrough[ib]->RX()) && (disableGoingThrough[ib]->Y() < character[ic]->DY() && character[ic]->DY() <= disableGoingThrough[ib]->Y()+degreeOfHit) && disableGoingThrough[ib]->Exists() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->Y() - 32);

				//�ǂ̍���p
				if( (disableGoingThrough[ib]->X()+degreeOfHit < character[ic]->RX() && character[ic]->RX() < disableGoingThrough[ib]->X()+haba) && (disableGoingThrough[ib]->Y()+degreeOfHit < character[ic]->DY() && character[ic]->DY() < disableGoingThrough[ib]->Y()+haba) && disableGoingThrough[ib]->Exists() == 1)character[ic]->SetX(disableGoingThrough[ib]->X()-32/*+degreeOfHit-character[ic]->GetMV()*/);
				//�ǂ̉E��p
				if( (disableGoingThrough[ib]->RX()-haba < character[ic]->X() && character[ic]->X() < disableGoingThrough[ib]->RX()-degreeOfHit) && (disableGoingThrough[ib]->Y()+degreeOfHit < character[ic]->DY() && character[ic]->DY() < disableGoingThrough[ib]->Y()+haba) && disableGoingThrough[ib]->Exists() == 1)character[ic]->SetX(disableGoingThrough[ib]->RX()/*-degreeOfHit+character[ic]->GetMV()*/);
				//�ǂ̍����p
				if( (disableGoingThrough[ib]->X()+degreeOfHit < character[ic]->RX() && character[ic]->RX() < disableGoingThrough[ib]->X()+haba) && (disableGoingThrough[ib]->DY()-haba < character[ic]->Y() && character[ic]->Y() < disableGoingThrough[ib]->DY()-degreeOfHit) && disableGoingThrough[ib]->Exists() == 1)character[ic]->SetX(disableGoingThrough[ib]->X()-32/*+degreeOfHit-character[ic]->GetMV()*/);
				//�ǂ̉E���p
				if( (disableGoingThrough[ib]->RX()-haba < character[ic]->X() && character[ic]->X() < disableGoingThrough[ib]->RX()-degreeOfHit) && (disableGoingThrough[ib]->DY()-haba < character[ic]->Y() && character[ic]->Y() < disableGoingThrough[ib]->DY()-degreeOfHit) && disableGoingThrough[ib]->Exists() == 1)character[ic]->SetX(disableGoingThrough[ib]->RX()/*-degreeOfHit+character[ic]->GetMV()*/);
	
			}
		}
	}


	int Collision::CheckOneUponAnother(int x1, int y1,int x2, int y2, int collisionLevel)
	{
		if( (x2 < x1+32-collisionLevel) && (x1+collisionLevel < x2+32) && (y1+collisionLevel < y2+32) && (y2 < y1+32-collisionLevel) )
			return 1;
		else 
			return 0;
	}


	void Collision::CheckCollisionWithFire()
	{
/*		std::list<Fire*>::iterator itrFire;
		std::list<ICollisionable*>::iterator itrHardBlock;
	
		for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
		{
			for(int k=1; k<=4; ++k)
			{
				for (int i = 0, fireSize=((*itrFire)->GetSize()-1)/4; i < fireSize; ++i)
				{
					if((*itrFire)->GetFlag(k+4*i) == 1)
					{
						int x_fire = (*itrFire)->GetX(k+4*i);
						int y_fire = (*itrFire)->GetY(k+4*i);
					
						for (itrHardBlock = hardBlock.begin(); itrHardBlock != hardBlock.end(); ++itrHardBlock)
						{
							int x_hblock = (*itrHardBlock)->X();
							int y_hblock = (*itrHardBlock)->Y();
						
							if(CheckOneUponAnother(x_hblock,y_hblock,x_fire,y_fire, collisionLevelWithFire) == 1)
							{
								(*itrFire)->SetFlag(k+4*i, 0);
							
								if(i+1 <= fireSize)
								{
									for (i++; i< fireSize; ++i)
									{
										(*itrFire)->SetFlag(k+4*i, 0);
									}
								}
								break;
							}
						}
					}
				}
			}
		}*/
	}


	void Collision::CheckCollisionFireAndFragile()
	{
/*		std::list<Fire*>::iterator itrFire;
		std::list<ICollisionable*>::iterator itrFragile;
	
		for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
		{
			for(int k=0; k<=4; ++k)
			{
				for (int i = 0, fireSize=((*itrFire)->GetSize()-1)/4; i < fireSize; ++i)
				{
					if((*itrFire)->GetFlag(k+4*i) == 1)
					{
						int x_fire = (*itrFire)->GetX(k+4*i);
						int y_fire = (*itrFire)->GetY(k+4*i);
					
						for (itrFragile = fragile.begin(); itrFragile != fragile.end(); ++itrFragile)
						{
							if((*itrFragile)->Exists())
							{
								int x_fragile = (*itrFragile)->X();
								int y_fragile = (*itrFragile)->Y();
						
								if (CheckOneUponAnother(x_fragile, y_fragile, x_fire, y_fire, collisionLevelWithFire))
								{
									(*itrFire)->SetFlag(k + 4 * i, 0);
									(*itrFragile)->SetExists(0);

									if (i + 1 <= fireSize)
									{
										for (i++; i < fireSize; ++i)
										{
											(*itrFire)->SetFlag(k + 4 * i, 0);
										}
									}
									break;
								}
							}
						}
					}
				}
			}
		}*/
	}


	void Collision::CheckCollisionItemAndCharactor()
	{
		std::vector<ICollisionable*>::iterator itrCharacter = character.begin();
		for(itrCharacter; itrCharacter != character.end(); ++itrCharacter)
		{
			Character *chara = dynamic_cast<Character*>(*itrCharacter);
			if(chara->Exists() == 1)
			{
				std::list<Item*>::iterator itrItem = item.begin();
				for (itrItem; itrItem != item.end(); ++itrItem)
				{
					if((*itrItem)->Exists() == 1)
					{
						if(CheckOneUponAnother((*itrItem)->X(), (*itrItem)->Y(), chara->X(), chara->Y(), degreeOfHit))
						{
//							switch ((*itrItem)->GetKind())
//							{
//							case Item::BOMB:
//								chara->IncrementBomb();
//								break;
//							case Item::FIRE:
//								chara->IncrementFireLevel();
//								break;
//							case Item::SPEED:
//								chara->IncrementSpeed();
//								break;
//							default:
//								break;
//							}
							(*itrItem)->SetExists(0);
						}
					}
				}
			}
		}

	}


	void Collision::CheckAllCollision()
	{
		CheckEnableToPass();
		CheckCollisionWithFire();
		CheckCollisionFireAndFragile();
		CheckCollisionItemAndCharactor();
	}
}
