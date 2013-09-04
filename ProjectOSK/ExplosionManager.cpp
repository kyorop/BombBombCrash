#include "ExplosionManager.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "MapObstacle.h"
#include "DxLib.h"

ExplosionManager::ExplosionManager():
	vex(new std::vector<Explosion*>(1))
{
	(*vex)[0] = new Explosion(0,0,0,0);//���̂̐������K�v
	//vex[0] = new Explosion(0,0,0,0);
}

void ExplosionManager::AddExplosion(int level)
{
	//��x��4�����₷(�l���ɍL���邩��)
	vex->push_back(new Explosion(level,0,0,0));
	vex->push_back(new Explosion(0,level,0,0));
	vex->push_back(new Explosion(0,0,level,0));
	vex->push_back(new Explosion(0,0,0,level));
}

void ExplosionManager::SetExplosion(const Bomb &bomb)
{
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->SetExplosion(bomb);//�{�����u����A���ꂪ����������A�΂𑶍݂�����
	}
}

void ExplosionManager::SetZahyou(const Bomb &bomb)
{
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->SetZahyou(bomb);//�{���̒u���ꂽ�ʒu����΂̍��W���߂�
	}
}

void ExplosionManager::CheckHitExplosion(Player *player)
{
	//this->explosion.CheckHIt(*player);
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->CheckHItCharactor(player);//�v���C���[�Ƃ̂����蔻��
	}
}

void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
{
	const int num = (vex->size() - 1) / 4; //�㉺���E�ɍL����΂̂����A���S�������e��̌�
	/*
	for(int i=0; i<num; i++)//��ʉ��ɍL�����
	{
		(*vex)[1+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[1+4*i]->GetFlag() == 0)//��ł��΂��ǂɂԂ�������A���̗�̂���ȍ~�̉΂͑S������
		//if(mapobstacle->GetFlag(vex[1+4*i]->y / 32)[] == FALSE)
		{
			if(i+1 <= num)
			{
				for(int j=i+1; j<num; j++)
				{
					(*vex)[1+4*j]->SetFlag(FALSE);
				}
			}	
			break;
		}
	}

	for(int i=0; i<num; i++)//��ʏ�ɍL�����
	{
		(*vex)[2+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[2+4*i]->GetFlag() == 0)//��ł��΂��ǂɂԂ�������A���̗�̂���ȍ~�̉΂͑S������
		{
			if(i+1 <= num)//�������ɂ��΂�����Ȃ�
			{
				for(int j=i+1; j<num; j++)
				{
					(*vex)[2+4*j]->SetFlag(FALSE);
				}
			}
			break;
		}
	}

	for(int i=0; i<num; i++)//��ʉE�ɍL�����
	{
		(*vex)[3+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[3+4*i]->GetFlag() == 0)//��ł��΂��ǂɂԂ�������A���̗�̂���ȍ~�̉΂͑S������
		{
			if(i+1 <= num)//�������ɂ��΂�����Ȃ�
			{
				for(int j=i+1; j<num; j++)
				{
					(*vex)[3+4*j]->SetFlag(FALSE);
				}
			}
			break;
		}
	}

	for(int i=0; i<num; i++)//��ʍ��ɍL�����
	{
		(*vex)[4+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[4+4*i]->GetFlag() == FALSE)//��ł��΂��ǂɂԂ�������A���̗�̂���ȍ~�̉΂͑S������
		{
			if(i+1 <= num)//�������ɂ��΂�����Ȃ�
			{
				for(int j=i+1; j<num; j++)
				{
					(*vex)[4+4*j]->SetFlag(FALSE);
				}
			}
			break;
		}
	}
	*/

	for(int k=1; k<5; k++)//k�͏����ʒu(���S�̉΂̂����ׂ̉�)
	{
		for(int i=0; i<num; i++)//��ʍ��ɍL�����
		{
			(*vex)[k+4*i]->CheckHitObject(mapobstacle);//�΂�4������

			if( (*vex)[k+4*i]->GetFlag() == FALSE)//��ł��΂��ǂɂԂ�������A���̗�̂���ȍ~�̉΂͑S������
			{
				if(i+1 <= num)//�������ɂ��΂�����Ȃ�
				{
					for(int j=i+1; j<num; j++)
					{
						(*vex)[k+4*j]->SetFlag(FALSE);
					}
				}
				continue;//���̉΂̗�Ɉڂ�
			}
		}
	}
}

void ExplosionManager::DrawExplosion(const Bomb &bomb)
{
	//this->explosion.Draw(map,bomb);
	if(Timer(1000))
	{
		for(int i=0,size=vex->size(); i<size; i++ )
		{
			(*vex)[i]->Draw(bomb);//flag��2�Ȃ�{����`��
		}
	}
	else//���Ԃ������������
	{
		for(int i=0,size=vex->size(); i<size; i++ )
		{
			(*vex)[i]->SetFlag(FALSE);
		}
	}
}

bool ExplosionManager::Timer(int time)
{
	static bool resetTime = true;
	static int startTime;

	if(resetTime == true)
	{
		startTime = GetNowCount();
		resetTime = false;
	}

	if(GetNowCount() - startTime < time)//3�b�Ԃ̓X�^�[�g���Ԃ����Z�b�g���Ȃ�
	{
		return TRUE;		//���e��\��������
	}
	else
	{
		resetTime = true;//3�b��������X�^�[�g���Ԃ����Z�b�g����
		return FALSE;		//���e������
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
