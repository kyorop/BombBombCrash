#include "BombManager.h"
#include "ItemManager.h"
#include "MapObstacle.h"
#include "Item.h"
#include "Object.h"
#include "Block.h"
#include "ExplosionManager.h"
#include "Map.h"
#include "Player.h"
#include "Explosion.h"
#include "Bomb.h"
#include "BlastManager.h"
#include "MapState.h"
#include "Enemy.h"
#include "EnemyBombManager.h"
#include "DxLib.h"
#include <iostream>
#include <vector>

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

	//_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	SetGraphMode(1024,768,16);
	ChangeWindowMode(true);
	if(DxLib_Init() == -1)
		return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	
	Map map;
	Player player;
	//Enemy enemy(32*14,32*11);
	const int enemyNum = 4;

	

	Enemy *enemy[enemyNum] = 
	{
		new Enemy(32*14, 32*1),
		new Enemy(32*2, 32*11),
		new Enemy(32*14, 32*11),
		new Enemy(32*8, 32*5)
	};
	Block block;
	ItemManager itemManager;
	BombManager pBomb;
	//EnemyBombManager enemyBombManager;
	EnemyBombManager eBomb[enemyNum];
	BlastManager pBlast;
	BlastManager eBlast[enemyNum];
	const int drawNum = 18;
	IDrawable *iDraw[drawNum];
	iDraw[0] = &map;
	iDraw[1] = &itemManager;
	iDraw[2] = &block;
	iDraw[3] = &pBomb;

	for (int i = 4,j = 0; i < 4+enemyNum && j<enemyNum; ++i, ++j)
	{
		iDraw[i] = &eBomb[j];
	}

	iDraw[4+enemyNum] = &player;

	for (int i = 4+enemyNum+1, j = 0; i < 4+enemyNum+1+4 && j<enemyNum; ++i, ++j)
	{
		iDraw[i] = enemy[j];
	}

	iDraw[4+enemyNum+1+4] = &pBlast;
	
	for (int i = 4+enemyNum+1+4+1, j = 0; i < 4+enemyNum+1+4+1+4 && j<enemyNum; ++i, ++j)
	{
		iDraw[i] = &eBlast[j];
	}
		
	const int registerNum = 8;
	IRegister *iRegister[registerNum]=
	{
		&map,
		&block,
		&player,
		&pBomb,
		&eBomb[0],
		&pBlast,
		&eBlast[0],
		&itemManager,
	};

	int g_lasttime = 0;
	float g_frametime = 0;

	//enemy.SetGoal(11,14);
	//int rNum = GetRand(enemy.i_goal.size()-1);
	//enemy.Initialize();
	//enemy.SetRoute(11,14,enemy.i_goal[rNum], enemy.j_goal[rNum]);
	itemManager.SetItem(block);

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();
		
		//計算部
		
		//登録部
		for(int i=0; i<registerNum; ++i)
		{
			iRegister[i]->Register();
		}
	
		//キャラの移動
		player.Move(g_lasttime);
		for (int i = 0; i < enemyNum; i++)
		{
			enemy[i]->Order();
			enemy[i]->Move(g_lasttime);
		}
	
		//Enemyのあたり判定
		for(int i=0; i<enemyNum; ++i)
		{
			for(int j=0; j<enemyNum; ++j)
			{
				//eBomb[i].CheckHit(enemy[j]);
			}
		}
		for (int i = 0; i < enemyNum; i++)
		{
			//map.CheckHitCharactor(enemy[i]);
			//block.CheckHit(enemy[i]);
			itemManager.CheckHitCharactor(enemy[i]);
		}

		//Playerのあたり判定
		pBomb.CheckHit(&player);
		map.CheckHitCharactor(&player);
		block.CheckHit(&player);
		itemManager.CheckHitCharactor(&player);

		//PlayerのBomb管理
		pBomb.AddBomb(player);
		pBomb.BombSet(player);
		pBomb.MaintainBomb();

		//EnemyのBomb管理
		for (int i = 0; i < enemyNum; i++)
		{
			eBomb[i].AddBomb(*enemy[i]);
			eBomb[i].BombSet(*enemy[i]);
			eBomb[i].MaintainBomb();
		}
		

		//PlayerのBlast管理
		pBlast.Add(player);
		pBlast.FireUp(player);
		pBlast.Set(pBomb);
		pBlast.Maintain(pBomb);
		pBlast.CheckHit(&block, &map, &player, &pBomb, &itemManager);

		//EnemyのBlast管理
		for (int i = 0; i < enemyNum; i++)
		{
			eBlast[i].Add(*enemy[i]);
			eBlast[i].FireUp(*enemy[i]);
			eBlast[i].Set(eBomb[i]);
			eBlast[i].Maintain(eBomb[i]);
			eBlast[i].CheckHit(&block, &map, &player, &eBomb[i], &itemManager);
		}
		//blastManager.CheckHitObject(&map);
		//blastManager.CheckHitObject(&block);
		//blastManager.CheckHitItem(&itemManager);
		//blastManager.CheckHitBomb(&bombManager);
		//blastManager.CheckHitCharactor(&player);
		

		//描画部
		for(int i=0; i<drawNum; ++i)
		{
			//if(i != 6)
			iDraw[i]->Draw();
		}
	
		int color = GetColor(255,255,255);
		DrawFormatString(640,0,color,"ボムアップ獲得数 %d 個",itemManager.GetBombState());
		DrawFormatString(850,0,color,"火力アップ獲得数 %d 個",itemManager.GetFireState());
		DrawFormatString(640,20,color,"フレームタイム　%f　秒",g_frametime);
		DrawFormatString(640,40,color,"出せるボム総数　%d　個",pBomb.size);
		DrawFormatString(640,60,color,"出せるボム数あと　%d　個",pBomb.size-pBomb.GetBombNum());
		
		//for(int i=0,size=blastManager.vblast->size();i<size;++i)
		//{
		//	for(int j=0,size=(*blastManager.vblast)[i]->vex->size();j<size;++j)
		//	{
		//		DrawFormatString(640+20*i,80+20*j,color,"%d"   , (*(*blastManager.vblast)[i]->vex)[j]->GetX());
		//		//DrawFormatString(640+20*i,80+20*j,color,"%d"   , (*(*blastManager.vblast)[i]->vex)[j]->GetExplosion());
		//		//DrawFormatString(640+20*i,80+20*j,color,"%d"   , (*blastManager.vblast)[i]->vex->size());
		//	}
		//}

		
		//for(int i=0,size=bombManager.vbomb->size();i<size;++i)
		//{
		//	DrawFormatString(640,80+20*i,color,"[%d]ボムフラグ　%d",i+1,(*bombManager.vbomb)[i]->GetFlag());
		//}

		for(int i=0; i<MapState::row; ++i)
		{
			for(int j=0; j<MapState::line; ++j)
			{
				DrawFormatString(640+15*j,80+15*i,color,"%d",MapState::GetInstance()->GetState(i,j,MAP));
			}
		}

		
		for(int n=0,size=enemy[0]->AI.i_goal.size(); n<size; ++n)
		{
			DrawFormatString(640, 80+15*15+15*n, color, "第%d行", enemy[0]->AI.i_goal[n]);
			DrawFormatString(640+15*5, 80+15*15+15*n, color, "第%d列", enemy[0]->AI.j_goal[n]);
		}
		
		//int n=0;
		//std::list<int>::iterator it = enemy[0]->AI.route.begin();
		for (int n=0, size=enemy[0]->AI.route.size(); n<size; ++n)
		{
			switch(enemy[0]->AI.route[n])
			{
			case 1:DrawFormatString(15*4*n, 80+15*15+15*8, color, "LEFT->");continue;
			case 2:DrawFormatString(15*4*n, 80+15*15+15*8, color, "RIGHT->");continue;
			case 3:DrawFormatString(15*4*n, 80+15*15+15*8, color, "UP->");continue;
			case 4:DrawFormatString(15*4*n, 80+15*15+15*8, color, "DOWN->");continue;
			}
		}
		


		//for(int i=0; i<ROW; ++i)
		//{
		//	for(int j=0; j<LINE; ++j)
		//	{
		//		DrawFormatString(640+15*j,80+15*i,color,"%d",MapState::GetInstance()->GetState(i,j,CHARACTOR));
		//	}
		//}
		
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;
	}

	for (int i = 0; i < enemyNum; ++i)
	{
		delete enemy[i];
	}

	DxLib_End();
	return 0;
}