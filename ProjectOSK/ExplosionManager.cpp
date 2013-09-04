#include "ExplosionManager.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "MapObstacle.h"
#include "DxLib.h"

ExplosionManager::ExplosionManager():
	vex(new std::vector<Explosion*>(1))
{
	(*vex)[0] = new Explosion(0,0,0,0);//実体の生成が必要
	//vex[0] = new Explosion(0,0,0,0);
}

void ExplosionManager::AddExplosion(int level)
{
	//一度に4枚増やす(四方に広がるから)
	vex->push_back(new Explosion(level,0,0,0));
	vex->push_back(new Explosion(0,level,0,0));
	vex->push_back(new Explosion(0,0,level,0));
	vex->push_back(new Explosion(0,0,0,level));
}

void ExplosionManager::SetExplosion(const Bomb &bomb)
{
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->SetExplosion(bomb);//ボムが置かれ、それが爆発したら、火を存在させる
	}
}

void ExplosionManager::SetZahyou(const Bomb &bomb)
{
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->SetZahyou(bomb);//ボムの置かれた位置から火の座標を定める
	}
}

void ExplosionManager::CheckHitExplosion(Player *player)
{
	//this->explosion.CheckHIt(*player);
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->CheckHItCharactor(player);//プレイヤーとのあたり判定
	}
}

void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
{
	const int num = (vex->size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
	/*
	for(int i=0; i<num; i++)//画面下に広がる火
	{
		(*vex)[1+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[1+4*i]->GetFlag() == 0)//一つでも火が壁にぶつかったら、その列のそれ以降の火は全部消す
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

	for(int i=0; i<num; i++)//画面上に広がる火
	{
		(*vex)[2+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[2+4*i]->GetFlag() == 0)//一つでも火が壁にぶつかったら、その列のそれ以降の火は全部消す
		{
			if(i+1 <= num)//もう次にも火があるなら
			{
				for(int j=i+1; j<num; j++)
				{
					(*vex)[2+4*j]->SetFlag(FALSE);
				}
			}
			break;
		}
	}

	for(int i=0; i<num; i++)//画面右に広がる火
	{
		(*vex)[3+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[3+4*i]->GetFlag() == 0)//一つでも火が壁にぶつかったら、その列のそれ以降の火は全部消す
		{
			if(i+1 <= num)//もう次にも火があるなら
			{
				for(int j=i+1; j<num; j++)
				{
					(*vex)[3+4*j]->SetFlag(FALSE);
				}
			}
			break;
		}
	}

	for(int i=0; i<num; i++)//画面左に広がる火
	{
		(*vex)[4+4*i]->CheckHitObject(mapobstacle);

		if( (*vex)[4+4*i]->GetFlag() == FALSE)//一つでも火が壁にぶつかったら、その列のそれ以降の火は全部消す
		{
			if(i+1 <= num)//もう次にも火があるなら
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

	for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火)
	{
		for(int i=0; i<num; i++)//画面左に広がる火
		{
			(*vex)[k+4*i]->CheckHitObject(mapobstacle);//火は4枚周期

			if( (*vex)[k+4*i]->GetFlag() == FALSE)//一つでも火が壁にぶつかったら、その列のそれ以降の火は全部消す
			{
				if(i+1 <= num)//もう次にも火があるなら
				{
					for(int j=i+1; j<num; j++)
					{
						(*vex)[k+4*j]->SetFlag(FALSE);
					}
				}
				continue;//次の火の列に移る
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
			(*vex)[i]->Draw(bomb);//flagが2ならボムを描く
		}
	}
	else//時間がたったら消す
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

	if(GetNowCount() - startTime < time)//3秒間はスタート時間をリセットしない
	{
		return TRUE;		//爆弾を表示させる
	}
	else
	{
		resetTime = true;//3秒たったらスタート時間をリセットする
		return FALSE;		//爆弾を消す
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
