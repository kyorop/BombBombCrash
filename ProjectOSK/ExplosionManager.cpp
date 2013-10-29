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

	//初期火力レベル、中心とその周り一マス
	vex.push_back(center);//中心
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
	++nowFireLevel;//次増やすときは、一個隣に増やす

	//一度に4枚増やす(四方に広がるから)
	Explosion *up =		new Explosion(0,0,0,0,nowFireLevel);
	Explosion *down =	new Explosion(0,0,0,nowFireLevel,0);
	Explosion *left =		new Explosion(0,0,nowFireLevel,0,0);
	Explosion *right =	new Explosion(0,nowFireLevel,0,0,0);
	vex.push_back(up);
	vex.push_back(down);
	vex.push_back(left);
	vex.push_back(right);
}

void ExplosionManager::Set(int x, int y)
{
	if(explosion == 0)//爆弾が置かれたら、
	{
		fuse = TRUE;//導火線に火がつく
		for(int i=0,size=vex.size(); i<size; ++i )
		{
			vex[i]->Set(x, y);
		}
	}
}

void ExplosionManager::Maintain()
{
	if(fuse == TRUE/* && bomb.GetFlag() == FALSE*/)//導火線に火がついたボムが消えたら
	{
		if(beforeExplosion.CountDown(timeBeforeExplosion) == 1)
		{
			this->fuse = FALSE;
			this->explosion = TRUE;//爆発
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