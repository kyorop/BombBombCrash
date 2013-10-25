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
	fuse(0),
	explosion(0),
	addFireNum(1),
	nowFireLevel(1),
	vex(),
	fireImage(LoadGraph("fire.bmp")),
	beforeExplosion()
{
	//初期火力レベル、中心とその周り一マス
	vex.push_back(new Explosion(0,0,0,0));
	vex.push_back(new Explosion(1,0,0,0));
	vex.push_back(new Explosion(0,1,0,0));
	vex.push_back(new Explosion(0,0,1,0));
	vex.push_back(new Explosion(0,0,0,1));
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
		vex.push_back(new Explosion(nowFireLevel,0,0,0));
		vex.push_back(new Explosion(0,nowFireLevel,0,0));
		vex.push_back(new Explosion(0,0,nowFireLevel,0));
		vex.push_back(new Explosion(0,0,0,nowFireLevel));
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

//void ExplosionManager::CheckHitCharactor(Charactor *charactor)
//{
//	//this->explosion.CheckHIt(*player);
//	if(this->explosion == TRUE)
//	{
//		for(int i=0,size=vex.size(); i<size; i++ )
//		{
//			vex[i]->CheckHItCharactor(charactor);//プレイヤーとのあたり判定
//		}
//	}
//}
//
//void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
//{
//	if(explosion == TRUE)
//	{
//		const int num = (vex.size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
//		
//		for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitObject(mapobstacle);//火は4枚周期
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//一つでも火が壁にぶつかって、
//				{
//					if(i+1 <= num)//もう次にも火があるなら
//					{
//						for(int j=i+1; j<num; j++)//その列のそれ以降の火は全部消す
//						{
//							vex[k+4*j]->SetExplosion(FALSE);
//						}
//					}
//				break;
//				//continue;//次の火の列に移る
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
//		const int num = (vex.size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
//		
//		for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitBomb(bomb);//火は4枚周期
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//一つでも火が壁にぶつかって、
//				{
//					if(i+1 <= num)//もう次にも火があるなら
//					{
//						for(int j=i+1; j<num; j++)//その列のそれ以降の火は全部消す
//						{
//							vex[k+4*j]->SetExplosion(FALSE);
//						}
//					}
//				break;
//				//continue;//次の火の列に移る
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
//		const int num = (vex.size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
//		
//		for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitItem(item);//火は4枚周期
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//一つでも火が壁にぶつかって、
//				{
//					if(i+1 <= num)//もう次にも火があるなら
//					{
//						for(int j=i+1; j<num; j++)//その列のそれ以降の火は全部消す
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
//		const int num = (vex.size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
//		
//		for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
//		{
//			for(int i=0; i<num; i++)
//			{
//				vex[k+4*i]->CheckHitObject(mapobstacle1);
//				vex[k+4*i]->CheckHitObject(mapobstacle2);
//				for(int j=0; j<ITEMNUM; ++j)
//					vex[k+4*i]->CheckHitItem(itemManager->GetItemInstance(j) );//火は4枚周期
//				for(int j=0,sizebomb=bombManager->bomb.size(); j<sizebomb; ++j)
//					vex[k+4*i]->CheckHitBomb(bombManager->GetBombObject(j) );
//				vex[k+4*i]->CheckHItCharactor(charactor);
//
//				if( vex[k+4*i]->GetExplosion() == FALSE)//一つでも火が壁にぶつかって、
//				{
//					if(i+1 <= num)//もう次にも火があるなら
//					{
//						for(int j=i+1; j<num; j++)//その列のそれ以降の火は全部消す
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
