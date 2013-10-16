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
#include "DxLib.h"

ExplosionManager::ExplosionManager():
	vex(new std::vector<Explosion*>(5))
{
	//�����Ἠ��x���A���S�Ƃ��̎����}�X
	(*vex)[0] = new Explosion(0,0,0,0);
	(*vex)[1] = new Explosion(1,0,0,0);
	(*vex)[2] = new Explosion(0,1,0,0);
	(*vex)[3] = new Explosion(0,0,1,0);
	(*vex)[4] = new Explosion(0,0,0,1);

	this->fuse = 0;
	this->explosion = 0;
	this->addFireNum = 1;
	this->nowFireLevel = 1;
}

void ExplosionManager::FireUp(const Charactor &charactor)
{
	if(charactor.GetFireLevel() > this->addFireNum)
	{
		++this->addFireNum;
		++this->nowFireLevel;//�����₷�Ƃ��́A��ׂɑ��₷

		//��x��4�����₷(�l���ɍL���邩��)
		vex->push_back(new Explosion(this->nowFireLevel,0,0,0));
		vex->push_back(new Explosion(0,this->nowFireLevel,0,0));
		vex->push_back(new Explosion(0,0,this->nowFireLevel,0));
		vex->push_back(new Explosion(0,0,0,this->nowFireLevel));
	}
}

void ExplosionManager::Set(Bomb &bomb)
{
	if(bomb.GetFlag() == TRUE && this->explosion == 0)//���e���u���ꂽ��A
	{
		this->fuse = TRUE;//���ΐ��ɉ΂���
		for(int i=0,size=vex->size(); i<size; ++i )
		{
			(*vex)[i]->Set(bomb);
		}
	}

	if(this->fuse == TRUE && bomb.GetFlag() == FALSE)//���ΐ��ɉ΂������{������������
	{
		this->fuse = FALSE;
		this->explosion = TRUE;//����
		for(int i=0,size=vex->size(); i<size; ++i )
		{
			(*vex)[i]->SetExplosion(TRUE);
		}
	}
if(this->explosion == TRUE && bomb.GetFlag() == FALSE)//���������t���[���̃{���t���O��FALSE�Ȃ̂ŁA���������ォ�������I������O�ɁA�{�����u���ꂽ���̔����̍��W�̍Ď擾��h����
	{                                                                                          //�������Ƀ{�����u����Ă����W�̍Ď擾���N����Ȃ��悤�ɂ��Ă���
		
	}
	

}

void ExplosionManager::Maintain()
{
	if(this->explosion == TRUE)
	{
		if(time.CountDown(200) == false)
			this->explosion = TRUE;
		else
		{
			this->explosion = FALSE;
			for(int i=0,size=vex->size(); i<size; i++ )
			{
				(*vex)[i]->SetExplosion(FALSE);
			}
		}
	}
}

void ExplosionManager::CheckHitCharactor(Charactor *charactor)
{
	//this->explosion.CheckHIt(*player);
	if(this->explosion == TRUE)
	{
		for(int i=0,size=vex->size(); i<size; i++ )
		{
			(*vex)[i]->CheckHItCharactor(charactor);//�v���C���[�Ƃ̂����蔻��
		}
	}
}

void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
{
	if(this->explosion == TRUE)
	{
		const int num = (vex->size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
		
		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
		{
			for(int i=0; i<num; i++)
			{
				(*vex)[k+4*i]->CheckHitObject(mapobstacle);//�΂�4������

				if( (*vex)[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
				{
					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
					{
						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
						{
							(*vex)[k+4*j]->SetExplosion(FALSE);
						}
					}
				break;
				//continue;//���̉΂̗�Ɉڂ�
				}
			}//for(i)
		}//for(k)
	}
}

void ExplosionManager::CheckHitBomb(Bomb *bomb)
{
	/*
	for(int i=0,size=vex->size(); i<size; ++i)
	{
		(*vex)[i]->CheckHitBomb(bomb);
	}
	*/

	if(this->explosion == TRUE)
	{
		const int num = (vex->size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
		
		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
		{
			for(int i=0; i<num; i++)
			{
				(*vex)[k+4*i]->CheckHitBomb(bomb);//�΂�4������

				if( (*vex)[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
				{
					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
					{
						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
						{
							(*vex)[k+4*j]->SetExplosion(FALSE);
						}
					}
				break;
				//continue;//���̉΂̗�Ɉڂ�
				}
			}//for(i)
		}//for(k)
	}

}

void ExplosionManager::CheckHitItem(Item *item)
{
	if(this->explosion == TRUE)
	{
		const int num = (vex->size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
		
		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
		{
			for(int i=0; i<num; i++)
			{
				(*vex)[k+4*i]->CheckHitItem(item);//�΂�4������

				if( (*vex)[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
				{
					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
					{
						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
						{
							(*vex)[k+4*j]->SetExplosion(FALSE);
						}
					}
				break;
				}
			}//for(i)
		}//for(k)
	}
}

void ExplosionManager::CheckHit(MapObstacle *mapobstacle1, MapObstacle *mapobstacle2, Charactor *charactor, BombManager *bombManager, ItemManager *itemManager)
{
	if(this->explosion == TRUE)
	{
		const int num = (vex->size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
		
		for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�); k��4�{�̔��������
		{
			for(int i=0; i<num; i++)
			{
				(*vex)[k+4*i]->CheckHitObject(mapobstacle1);
				(*vex)[k+4*i]->CheckHitObject(mapobstacle2);
				for(int j=0; j<ITEMNUM; ++j)
					(*vex)[k+4*i]->CheckHitItem(itemManager->GetItemInstance(j) );//�΂�4������
				for(int j=0,sizebomb=bombManager->vbomb->size(); j<sizebomb; ++j)
					(*vex)[k+4*i]->CheckHitBomb(bombManager->GetBombObject(j) );
				(*vex)[k+4*i]->CheckHItCharactor(charactor);

				if( (*vex)[k+4*i]->GetExplosion() == FALSE)//��ł��΂��ǂɂԂ����āA
				{
					if(i+1 <= num)//�������ɂ��΂�����Ȃ�
					{
						for(int j=i+1; j<num; j++)//���̗�̂���ȍ~�̉΂͑S������
						{
							(*vex)[k+4*j]->SetExplosion(FALSE);
						}
					}
				break;
				}
			}//for(i)
		}//for(k)
	}
}

void ExplosionManager::Draw()
{
	if(this->explosion == TRUE)
	{
		for(int i=0,size=vex->size(); i<size; ++i )
		{
			(*vex)[i]->Draw();
		}
	}
}

ExplosionManager::~ExplosionManager(void)
{
	std::vector<Explosion*>::iterator it = vex->begin();

	for(it; it != vex->end(); ++it)
	{
		delete *it;
	}
	delete vex;
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
	for(int i=0,size=vex->size(); i<size; ++i )
	{
		if((*vex)[i]->GetExplosion() == 0)
			MapState::GetInstance()->SetFireState((*vex)[i]->GetX(), (*vex)[i]->GetY(), 0);
		else if((*vex)[i]->GetExplosion() == 1)
			MapState::GetInstance()->SetFireState((*vex)[i]->GetX(), (*vex)[i]->GetY(), 1);
	}
}
