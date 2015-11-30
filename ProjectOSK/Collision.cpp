#include "Collision.h"
#include "ICollisionable.h"
#include "Bomb.h"
#include "MapObstacle.h"
#include "Player.h"
#include "Enemy.h"
#include "MapObject.h"
#include "ExplosionManager.h"
#include "Item.h"
#include "Charactor.h"


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
			//����
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);//�r��
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);//�ア����
	
			//����
			if((disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit <= character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()- 32);//�r��
			if((disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit <=character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX() - 32);//�ア����

			//��
			//��
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());//���s��
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());//�E�s��

			//��
			//��
			if( (disableGoingThrough[ib]->GetY()< character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY()-32);//���s��
			if( (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX()+degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && disableGoingThrough[ib]->GetFlag()== TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY()-32);//�E�s��

			//�^��
			if( (disableGoingThrough[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetRX()-degreeOfHit < character[ic]->GetX() && character[ic]->GetX() <= disableGoingThrough[ib]->GetRX()) && disableGoingThrough[ib]->GetFlag() == TRUE )character[ic]->SetX(disableGoingThrough[ib]->GetX() + 32);

			//�^�E
			if( (disableGoingThrough[ib]->GetY() <= character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetY()+degreeOfHit) && (disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX()- 32);
			if( (disableGoingThrough[ib]->GetDY()-degreeOfHit <= character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetDY()) && (disableGoingThrough[ib]->GetX() <= character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetX(disableGoingThrough[ib]->GetX() - 32);

			//�^��
			if( (disableGoingThrough[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetDY()-degreeOfHit < character[ic]->GetY() && character[ic]->GetY() <= disableGoingThrough[ib]->GetDY()) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetDY());

			//�^��
			if( (disableGoingThrough[ib]->GetX() <= character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetX()+degreeOfHit) && (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY() - 32);
			if( (disableGoingThrough[ib]->GetRX()-degreeOfHit <= character[ic]->GetRX() && character[ic]->GetRX() <= disableGoingThrough[ib]->GetRX()) && (disableGoingThrough[ib]->GetY() < character[ic]->GetDY() && character[ic]->GetDY() <= disableGoingThrough[ib]->GetY()+degreeOfHit) && disableGoingThrough[ib]->GetFlag() == TRUE)character[ic]->SetY(disableGoingThrough[ib]->GetY() - 32);

			//�ǂ̍���p
			if( (disableGoingThrough[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+haba) && (disableGoingThrough[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetY()+haba) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//�ǂ̉E��p
			if( (disableGoingThrough[ib]->GetRX()-haba < character[ic]->GetX() && character[ic]->GetX() < disableGoingThrough[ib]->GetRX()-degreeOfHit) && (disableGoingThrough[ib]->GetY()+degreeOfHit < character[ic]->GetDY() && character[ic]->GetDY() < disableGoingThrough[ib]->GetY()+haba) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetRX()/*-degreeOfHit+character[ic]->GetMV()*/);
			//�ǂ̍����p
			if( (disableGoingThrough[ib]->GetX()+degreeOfHit < character[ic]->GetRX() && character[ic]->GetRX() < disableGoingThrough[ib]->GetX()+haba) && (disableGoingThrough[ib]->GetDY()-haba < character[ic]->GetY() && character[ic]->GetY() < disableGoingThrough[ib]->GetDY()-degreeOfHit) && disableGoingThrough[ib]->GetFlag() == 1)character[ic]->SetX(disableGoingThrough[ib]->GetX()-32/*+degreeOfHit-character[ic]->GetMV()*/);
			//�ǂ̉E���p
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
	
	//���锚�������o����
	for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
	{
		for(int k=1; k<=4; ++k)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔�������
		{
			//���̃��[�v��,�����̉΂��ׂĂ���[�v����
			for (int i = 0, fireSize=((*itrFire)->GetSize()-1)/4; i < fireSize; ++i)
			{
				if((*itrFire)->GetFlag(k+4*i) == 1)
				{
					int x_fire = (*itrFire)->GetX(k+4*i);
					int y_fire = (*itrFire)->GetY(k+4*i);
					
					//�����}�X�̉΂ɑ΂��āA�S�Ẵn�[�h�u���b�N���
					for (itrHardBlock = hardBlock.begin(); itrHardBlock != hardBlock.end(); ++itrHardBlock)
					{
						int x_hblock = (*itrHardBlock)->GetX();
						int y_hblock = (*itrHardBlock)->GetY();
						
						//�n�[�h�u���b�N�Ɠ�������
						if(CheckOneUponAnother(x_hblock,y_hblock,x_fire,y_fire, collisionLevelWithFire) == 1)
						{
							(*itrFire)->SetFlag(k+4*i, 0);
							
							if(i+1 <= fireSize)//��ł���������̂ŁA���̃}�X�ɂ܂��΂���������
							{
								for (i++; i< fireSize; ++i)//����ȍ~���ׂď���
								{
									(*itrFire)->SetFlag(k+4*i, 0);
								}
							}
							break;//������break����΁A��� i ��}�b�N�X�܂Ń��[�v���Ă��܂����̂�
						}			   //�ŏ��� i �̃��[�v�����ɔ�������
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
	
	//���锚�������o����
	for (itrFire=fire.begin(); itrFire != fire.end() ; ++itrFire)
	{
		for(int k=0; k<=4; ++k)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔�������
		{
			//���̃��[�v��,�����̉΂��ׂĂ���[�v����
			for (int i = 0, fireSize=((*itrFire)->GetSize()-1)/4; i < fireSize; ++i)
			{
				if((*itrFire)->GetFlag(k+4*i) == 1)
				{
					int x_fire = (*itrFire)->GetX(k+4*i);
					int y_fire = (*itrFire)->GetY(k+4*i);
					
					//�����}�X�̉΂ɑ΂��āA�S�Ẳ��镨���
					for (itrFragile = fragile.begin(); itrFragile != fragile.end(); ++itrFragile)
					{
						if((*itrFragile)->GetFlag())
						{
							int x_fragile = (*itrFragile)->GetX();
							int y_fragile = (*itrFragile)->GetY();
						
							//���镨�Ɠ�������
							if(CheckOneUponAnother(x_fragile,y_fragile,x_fire,y_fire, collisionLevelWithFire))
							{
								(*itrFire)->SetFlag(k+4*i, 0);
								(*itrFragile)->SetFlag(0);
							
								if(i+1 <= fireSize)//��ł���������̂ŁA���̃}�X�ɂ܂��΂���������
								{
									for (i++; i< fireSize; ++i)//����ȍ~���ׂď���
									{
										(*itrFire)->SetFlag(k+4*i, 0);
									}
								}
								break;//������break����΁A��� i ��}�b�N�X�܂Ń��[�v���Ă��܂����̂�
							}			   //�ŏ��� i �̃��[�v�����ɔ�������
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
		Character *chara = dynamic_cast<Character*>(*itrCharacter);
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
							chara->IncrementBomb();
							break;
						case Item::FIRE:
							chara->IncrementFirepower();
							break;
						case Item::SPEED:
							chara->IncrementSpeed();
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
