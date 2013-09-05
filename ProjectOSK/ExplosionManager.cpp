#include "ExplosionManager.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "MapObstacle.h"
#include "ItemManager.h"
#include "BombManager.h"
#include "DxLib.h"
enum firestate
{
	FIREOFF,
	FIREON,
	EXPLOSION,
};

ExplosionManager::ExplosionManager():
	vex(new std::vector<Explosion*>(5))
{
	//初期火力レベル、中心とその周り一マス
	(*vex)[0] = new Explosion(0,0,0,0);
	(*vex)[1] = new Explosion(1,0,0,0);
	(*vex)[2] = new Explosion(0,1,0,0);
	(*vex)[3] = new Explosion(0,0,1,0);
	(*vex)[4] = new Explosion(0,0,0,1);

	addFireNum = 0;
	nowFireLevel = 1;
	this->flag = FIREOFF;
}

void ExplosionManager::Add(const ItemManager &manageItem)
{
	if(manageItem.GetFireState() > this->addFireNum)
	{
		++this->addFireNum;
		++this->nowFireLevel;//次増やすときは、一個隣に増やす

		//一度に4枚増やす(四方に広がるから)
		vex->push_back(new Explosion(this->nowFireLevel,0,0,0));
		vex->push_back(new Explosion(0,this->nowFireLevel,0,0));
		vex->push_back(new Explosion(0,0,this->nowFireLevel,0));
		vex->push_back(new Explosion(0,0,0,this->nowFireLevel));
	}
}

void ExplosionManager::Set(Bomb &bomb)
{
	if(bomb.GetFlag() == true)
		this->flag = FIREON;

	if(this->flag == FIREON && bomb.GetFlag() == false)
	{
		for(int i=0,size=vex->size(); i<size; i++ )
		{
			(*vex)[i]->SetExplosion(bomb.GetX(), bomb.GetY());
		}
		this->flag = EXPLOSION;
	}
}

void ExplosionManager::Maintain()
{
	if(this->flag == EXPLOSION)
	{
		if(time.CountDown(1000) == false)
			this->flag = EXPLOSION;
		else
			this->flag = FIREOFF;
	}
}

void ExplosionManager::CheckHitExplosion(Player *player)
{
	//this->explosion.CheckHIt(*player);
	if(this->flag == EXPLOSION)
	{
		for(int i=0,size=vex->size(); i<size; i++ )
		{
			(*vex)[i]->CheckHItCharactor(player);//プレイヤーとのあたり判定
		}
	}
}

void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
{
	if(this->flag == EXPLOSION)
	{
		const int num = (vex->size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
		
		for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
		{
			for(int i=0; i<num; i++)
			{
				(*vex)[k+4*i]->CheckHitObject(mapobstacle);//火は4枚周期

				if( (*vex)[k+4*i]->GetFlag() == FALSE)//一つでも火が壁にぶつかって、
				{
					if(i+1 <= num)//もう次にも火があるなら
					{
						for(int j=i+1; j<num; j++)//その列のそれ以降の火は全部消す
						{
							(*vex)[k+4*j]->SetFlag(FIREOFF);
						}
					}
				break;
				//continue;//次の火の列に移る
				}
			}//for(i)
		}//for(k)
	}
}

void ExplosionManager::Draw()
{
	if(this->flag)
	{
		for(int i=0,size=vex->size(); i<size; i++ )
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

void ExplosionManager::SetFlag(firestate flag)
{
	this->flag = flag;
}

firestate ExplosionManager::GetFlag()const
{
	return this->flag;
}