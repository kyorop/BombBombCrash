#include "ExplosionManager.h"
#include "Explosion.h"
#include "Bomb.h"
#include "MapState.h"
#include "Collision.h"
#include "Image.h"

ExplosionManager::ExplosionManager()
	:nowFireLevel(1),
	fuse(0),
	explosion(0),
	beforeExplosion(),
	image_fire(Image::GetInstance()->GetImage(Image::FIRE)),
	vex()
{
	Collision::GetInstance()->RegisterWithFire(this);
	Explosion *center = new Explosion(0,0,0,0);
	Explosion *up = new Explosion(0,0,0,1);
	Explosion *down = new Explosion(0,0,1,0);
	Explosion *left = new Explosion(0,1,0,0);
	Explosion *right = new Explosion(1,0,0,0);

	//�����Ἠ��x���A���S�Ƃ��̎����}�X
	vex.push_back(center);//���S
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
	++nowFireLevel;//�����₷�Ƃ��́A��ׂɑ��₷

	//��x��4�����₷(�l���ɍL���邩��)
	Explosion *up =		new Explosion(0,0,0,nowFireLevel);
	Explosion *down =	new Explosion(0,0,nowFireLevel,0);
	Explosion *left =		new Explosion(0,nowFireLevel,0,0);
	Explosion *right =	new Explosion(nowFireLevel,0,0,0);
	vex.push_back(up);
	vex.push_back(down);
	vex.push_back(left);
	vex.push_back(right);
}

void ExplosionManager::Update(const Bomb &bomb)
{
	if(bomb.GetFlag() && explosion == 0 && fuse == 0)//���e���u���ꂽ��A
	{
		fuse = TRUE;//���ΐ��ɉ΂���
		for(int i=0,size=vex.size(); i<size; ++i )
		{
			vex[i]->Set(bomb.GetX(), bomb.GetY());
		}
	}

	if(fuse == TRUE && bomb.GetFlag() == FALSE)//���ΐ��ɉ΂������{������������
	{
		 fuse = FALSE;
		 explosion = TRUE;//����
		 for(int i=0,size=vex.size(); i<size; ++i )
		{
			vex[i]->SetExplosion(TRUE);
		}
	}

	Maintain();
}

void ExplosionManager::Maintain()
{
	if(explosion == TRUE)
	{
		if(retainFire.CountDownFrame(displayingTime) == true)
		{
			explosion = FALSE;
			for(int i=0,size=vex.size(); i<size; i++ )
			{
				vex[i]->SetExplosion(FALSE);
			}
		}
	}
}

void ExplosionManager::Draw()
{
	if(this->explosion == TRUE)
	{
		for(int i=0,size=vex.size(); i<size; ++i )
		{
			if(vex[i]->GetExplosion() == 1)
				DrawGraph(vex[i]->GetX(), vex[i]->GetY(), image_fire, FALSE);
		}
	}
}

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

int ExplosionManager::GetExplosion(void)
{
	return explosion;
}

int ExplosionManager::Firepower(void)
{
	return nowFireLevel;
}
