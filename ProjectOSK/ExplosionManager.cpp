#include "ExplosionManager.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "Charactor.h"
#include "MapObstacle.h"
#include "ItemManager.h"
#include "BombManager.h"
#include "Item.h"
#include "MapState.h"
#include "Collision.h"
#include "DxLib.h"

ExplosionManager::ExplosionManager():
	fuse(0),
	explosion(0),
	addFireNum(1),
	nowFireLevel(1),
	vex(),
	fireImage(LoadGraph("fire.bmp")),
	beforeExplosion()
{
	Explosion *center = new Explosion(1,0,0,0,0);
	Explosion *up = new Explosion(0,0,0,0,1);
	Explosion *down = new Explosion(0,0,0,1,0);
	Explosion *left = new Explosion(0,0,1,0,0);
	Explosion *right = new Explosion(0,1,0,0,0);

	//���S��Collision�ɓo�^
	//Collision::GetInstance()->RegisterWithFire(center);

	//�����Ἠ��x���A���S�Ƃ��̎����}�X
	vex.push_back(center);//���S
	//center->SetNext(up);
	//center->SetNext(down);
	//center->SetNext(left);
	//center->SetNext(right);

	vex.push_back(up);
	vex.push_back(down);
	vex.push_back(left);
	vex.push_back(right);
}

ExplosionManager::~ExplosionManager(void)
{
	std::vector<Explosion*>::iterator it = vex.begin();
	for(it; it != vex.end(); ++it)
	{
		delete *it;
	}
}

void ExplosionManager::FireUp()
{
	++addFireNum;
	++nowFireLevel;//�����₷�Ƃ��́A��ׂɑ��₷

	//��x��4�����₷(�l���ɍL���邩��)
	Explosion *up =		new Explosion(0,0,0,0,nowFireLevel);
	Explosion *down =	new Explosion(0,0,0,nowFireLevel,0);
	Explosion *left =		new Explosion(0,0,nowFireLevel,0,0);
	Explosion *right =	new Explosion(0,nowFireLevel,0,0,0);
	vex.push_back(up);
	//vex[1+(nowFireLevel-1)*4]->SetNext(up);
	vex.push_back(down);
	//vex[2+(nowFireLevel-1)*4]->SetNext(down);
	vex.push_back(left);
	//vex[3+(nowFireLevel-1)*4]->SetNext(left);
	vex.push_back(right);
	//vex[4+(nowFireLevel-1)*4]->SetNext(right);
}

void ExplosionManager::Set(int x, int y)
{
	if(explosion == 0)//���e���u���ꂽ��A
	{
		fuse = TRUE;//���ΐ��ɉ΂���
		for(int i=0,size=vex.size(); i<size; ++i )
		{
			vex[i]->Set(x, y);
		}
	}
}

void ExplosionManager::Maintain()
{
	if(fuse == TRUE/* && bomb.GetFlag() == FALSE*/)//���ΐ��ɉ΂������{������������
	{
		if(beforeExplosion.CountDown(timeBeforeExplosion) == 1)
		{
			this->fuse = FALSE;
			this->explosion = TRUE;//����
			for(int i=0,size=vex.size(); i<size; ++i )
			{
				vex[i]->SetExplosion(TRUE);
			}
		}
	}

	if(this->explosion == TRUE)
	{
		if(retainFire.CountDown(displayingTime) == false)
			this->explosion = TRUE;
		else
		{
			this->explosion = FALSE;
			for(int i=0,size=vex.size(); i<size; i++ )
			{
				vex[i]->SetExplosion(FALSE);
			}
		}
	}
}

//void ExplosionManager::CheckHitCharactor(Charactor *charactor)
//{
//	//this->explosion.CheckHIt(*player);
//	if(this->explosion == TRUE)
//	{
//		for(int i=0,size=vex.size(); i<size; i++ )
//		{
//			vex[i]->CheckHItCharactor(charactor);//�v���C���[�Ƃ̂����蔻��
//		}
//	}
//}
//
//void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
//{
//	if(explosion == TRUE)
//	{
//		const int num = (vex.size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
//		
//		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitObject(mapobstacle);//�΂�4������
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
//				{
//					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
//					{
//						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
//						{
//							vex[k+4*j]->SetExplosion(FALSE);
//						}
//					}
//				break;
//				//continue;//���̉΂̗�Ɉڂ�
//				}
//			}//for(i)
//		}//for(k)
//	}
//}
//
//void ExplosionManager::CheckHitBomb(Bomb *bomb)
//{
//	/*
//	for(int i=0,size=vex->size(); i<size; ++i)
//	{
//		(*vex)[i]->CheckHitBomb(bomb);
//	}
//	*/
//
//	if(explosion == TRUE)
//	{
//		const int num = (vex.size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
//		
//		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitBomb(bomb);//�΂�4������
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
//				{
//					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
//					{
//						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
//						{
//							vex[k+4*j]->SetExplosion(FALSE);
//						}
//					}
//				break;
//				//continue;//���̉΂̗�Ɉڂ�
//				}
//			}//for(i)
//		}//for(k)
//	}
//
//}
//
//void ExplosionManager::CheckHitItem(Item *item)
//{
//	if(explosion == TRUE)
//	{
//		const int num = (vex.size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
//		
//		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitItem(item);//�΂�4������
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
//				{
//					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
//					{
//						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
//						{
//							vex[k+4*j]->SetExplosion(FALSE);
//						}
//					}
//				break;
//				}
//			}//for(i)
//		}//for(k)
//	}
//}
//
//void ExplosionManager::CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager)
//{
//	if(this->explosion == TRUE)
//	{
//		const int num = (vex.size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
//		
//		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitObject(mapobstacle1);
//				vex[k+4*i]->CheckHitObject(mapobstacle2);
//				for(int j=0; j<ITEMNUM; ++j)
//					vex[k+4*i]->CheckHitItem(itemManager->GetItemInstance(j) );//�΂�4������
//				for(int j=0,sizebomb=bombManager->bomb.size(); j<sizebomb; ++j)
//					vex[k+4*i]->CheckHitBomb(bombManager->GetBombObject(j) );
//				vex[k+4*i]->CheckHItCharactor(charactor);
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
//				{
//					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
//					{
//						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
//						{
//							vex[k+4*j]->SetExplosion(FALSE);
//						}
//					}
//				break;
//				}
//			}//for(i)
//		}//for(k)
//	}
//}

void ExplosionManager::Draw()
{
	if(this->explosion == TRUE)
	{
		for(int i=0,size=vex.size(); i<size; ++i )
		{
			if(vex[i]->GetExplosion() == 1)
				DrawGraph(vex[i]->GetX(), vex[i]->GetY(), fireImage, FALSE);
		}
	}
}

/*
void ExplosionManager::SetFlag(firestate flag)
{
	this->flag = flag;
}

firestate ExplosionManager::GetFlag()const
{
	return this->flag;
}
*/

void ExplosionManager::Register(void)
{
	for(int i=0,size=vex.size(); i<size; ++i )
	{
		if(vex[i]->GetExplosion() == 0)
			MapState::GetInstance()->SetFireState(vex[i]->GetX(), vex[i]->GetY(), 0);
		else if(vex[i]->GetExplosion() == 1)
			MapState::GetInstance()->SetFireState(vex[i]->GetX(), vex[i]->GetY(), 1);
	}
}

int ExplosionManager::GetX(int i)const
{
	return vex[i]->GetX();
}

int ExplosionManager::GetRX(int i)const
{
	return vex[i]->GetRX();
}

int ExplosionManager::GetY(int i)const
{
	return vex[i]->GetY();
}

int ExplosionManager::GetDY(int i)const
{
	return vex[i]->GetDY();
}

int ExplosionManager::GetFlag(int i)const
{
	return vex[i]->GetExplosion();
}

int ExplosionManager::GetSize()const
{
	return vex.size();
}

void ExplosionManager::SetFlag(int i, int flag)
{
	vex[i]->SetExplosion(flag);
}