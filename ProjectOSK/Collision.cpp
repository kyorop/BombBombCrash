#include "Collision.h"
#include "ICollisionable.h"
#include "PlayerBomb.h"
#include "EnemyBomb.h"
#include "Bomb.h"
#include "MapObstacle.h"
#include "Player.h"
#include "Enemy.h"
#include "MapObject.h"
#include "Map.h"
#include "DxLib.h"
#include "Explosion.h"
#include "ExplosionManager.h"
#include "Item.h"
#include "Charactor.h"
#include <typeinfo.h>



Collision::Collision(void)
	:disableGoingThrough(),
	bomb(),
	character(),
	softBlock(),
	hardBlock(),
	map(),
	fire(),
	fragile(),
	item()
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

void Collision::Finalize()
{
	disableGoingThrough.clear();
	bomb.clear();
	character.clear();
	softBlock.clear();
	hardBlock.clear();
	map.clear();
	fire.clear();
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
		if(map->GetId() == MapObstacle::HARDBLOCK)
		{
			hardBlock.push_back(anythingCollisionable);
			disableGoingThrough.push_back(anythingCollisionable);
		}
		else if(map->GetId() == MapObstacle::SOFTBLOCK)
		{
			softBlock.push_back(anythingCollisionable);
			disableGoingThrough.push_back(anythingCollisionable);
			fragile.push_front(anythingCollisionable);
		}
	}
}

void Collision::RegisterWithFire(ExplosionManager *pFire)
{
	fire.push_back(pFire);
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
			//□←
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);//途中
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);//上いった
	
			//→□
			if((disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()- 32);//途中
			if((disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit <=character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX() - 32);//上いった

			//□
			//↑
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());//左行く
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());//右行く

			//↓
			//□
			if( (disableGoingThrough[ib]->GetY()< character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY()-32);//左行く
			if( (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag()== TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY()-32);//右行く

			//真左
			if( (disableGoingThrough[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && disableGoingThrough[ib]->GetFlag() == TRUE )character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);

			//真右
			if( (disableGoingThrough[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX()- 32);
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() - 32);

			//真上
			if( (disableGoingThrough[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());

			//真下
			if( (disableGoingThrough[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY() - 32);
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY() - 32);

			//壁の左上角
			if( (disableGoingThrough[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+haba) && (disableGoingThrough[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetY()+haba) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//壁の右上角
			if( (disableGoingThrough[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetY()+haba) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
			//壁の左下角
			if( (disableGoingThrough[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+haba) && (disableGoingThrough[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//壁の右下角
			if( (disableGoingThrough[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && (disableGoingThrough[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
	
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
	std::list<ExplosionManager*>::iterator itrFire;
	std::list<ICollisionable*>::iterator itrHardBlock;
	
	//ある爆発を一つ抽出する
	for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
	{
		for(int k=1; k<=4; ++k)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
		{
			//下のループで,ある列の火すべてをループする
			for (int i = 0, fireSize=((*itrFire)->GetSize()-1)/4; i < fireSize; ++i)
			{
				if((*itrFire)->GetFlag(k+4*i) == 1)
				{
					int x_fire = (*itrFire)->GetX(k+4*i);
					int y_fire = (*itrFire)->GetY(k+4*i);
					
					//ある一マスの火に対して、全てのハードブロックを回す
					for (itrHardBlock = hardBlock.begin(); itrHardBlock != hardBlock.end(); ++itrHardBlock)
					{
						int x_hblock = (*itrHardBlock)->GetX();
						int y_hblock = (*itrHardBlock)->GetY();
						
						//ハードブロックと当ったら
						if(CheckOneUponAnother(x_hblock,y_hblock,x_fire,y_fire, collisionLevelWithFire) == 1)
						{
							(*itrFire)->SetFlag(k+4*i, 0);
							
							if(i+1 <= fireSize)//一つでも当たったので、次のマスにまだ火があったら
							{
								for (i++; i< fireSize; ++i)//それ以降すべて消す
								{
									(*itrFire)->SetFlag(k+4*i, 0);
								}
							}
							break;//ここでbreakすれば、上で i をマックスまでループしてしまったので
						}			   //最初の i のループも勝手に抜けられる
					}
				}
			}
		}
	}
}

void Collision::CheckCollisionFireAndFragile()
{
	std::list<ExplosionManager*>::iterator itrFire;
	std::list<ICollisionable*>::iterator itrFragile;
	
	//ある爆発を一つ抽出する
	for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
	{
		for(int k=1; k<=4; ++k)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
		{
			//下のループで,ある列の火すべてをループする
			for (int i = 0, fireSize=((*itrFire)->GetSize()-1)/4; i < fireSize; ++i)
			{
				if((*itrFire)->GetFlag(k+4*i) == 1)
				{
					int x_fire = (*itrFire)->GetX(k+4*i);
					int y_fire = (*itrFire)->GetY(k+4*i);
					
					//ある一マスの火に対して、全てのハードブロックを回す
					for (itrFragile = fragile.begin(); itrFragile != fragile.end(); ++itrFragile)
					{
						if((*itrFragile)->GetFlag() == 1)
						{
							int x_fragile = (*itrFragile)->GetX();
							int y_fragile = (*itrFragile)->GetY();
						
							//ハードブロックと当ったら
							if(CheckOneUponAnother(x_fragile,y_fragile,x_fire,y_fire, collisionLevelWithFire) == 1)
							{
								(*itrFire)->SetFlag(k+4*i, 0);
								(*itrFragile)->SetFlag(0);
							
								if(i+1 <= fireSize)//一つでも当たったので、次のマスにまだ火があったら
								{
									for (i++; i< fireSize; ++i)//それ以降すべて消す
									{
										(*itrFire)->SetFlag(k+4*i, 0);
									}
								}
								break;//ここでbreakすれば、上で i をマックスまでループしてしまったので
							}			   //最初の i のループも勝手に抜けられる
						}
					}
				}
			}
		}
	}
}

void Collision::CheckCollisionItemAndCharactor()
{
	std::vector<ICollisionable*>::iterator itrCharacter = character.begin();
	for(itrCharacter; itrCharacter != character.end(); ++itrCharacter)
	{
		Charactor *chara = dynamic_cast<Charactor*>(*itrCharacter);
		if(chara->GetFlag() == 1)
		{
			std::list<Item*>::iterator itrItem = item.begin();
			for (itrItem; itrItem != item.end(); ++itrItem)
			{
				if((*itrItem)->GetFlag() == 1)
				{
					if(CheckOneUponAnother((*itrItem)->GetX(), (*itrItem)->GetY(), chara->GetX(), chara->GetY(), degreeOfHit))
					{
						switch ((*itrItem)->GetKind())
						{
						case Item::BOMB:
							chara->AddBombNum();
							break;
						case Item::FIRE:
							chara->AddFireLevel();
							break;
						case Item::SPEED:
							chara->AddMV();
							break;
						default:
							break;
						}
						(*itrItem)->SetFlag(0);
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
