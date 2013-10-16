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
#include "EnemyBombManager.h"
#include "DxLib.h"
#include "DangerState.h"
#include "EnemyAI.h"
#include "Enemy.h"
#include "Route.h"
#include <iostream>
#include <vector>
#define DRAWNUM 9
#define REGISTERNUM 7

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	SetGraphMode(1024,768,16);
	ChangeWindowMode(true);
	if(DxLib_Init() == -1)
		return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	
	Map map;
	Player player;
	Enemy enemy(32*14,32*11);
	Block block;
	ItemManager itemManager;
	BombManager bombManager;
	EnemyBombManager enemyBombManager;
	BlastManager blastManager;
	BlastManager enemyBlastManager;
	
	IDrawable *iDraw[DRAWNUM]=
	{
		&map,
		&itemManager,
		&block,
		&bombManager,
		&enemyBombManager,
		&player,
		&enemy,
		&blastManager,
		&enemyBlastManager,
	};
	IRegister *iRegister[REGISTERNUM]=
	{
		&map,
		&block,
		&player,
		&enemy,
		&blastManager,
		&enemyBlastManager,
		&itemManager,
	};


	int g_lasttime = 0;
	float g_frametime = 0;

	//map.Register();
	

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
		for(int i=0; i<REGISTERNUM; ++i)
		{
			iRegister[i]->Register();
		}

		bombManager.Register(player);
		enemyBombManager.Register(enemy);
	
		//キャラの移動
		player.Move(g_lasttime);
		enemy.Order();
		enemy.Move(g_lasttime);
	
		//Enemyのあたり判定
		bombManager.CheckHit(&enemy);
		//map.CheckHitCharactor(&enemy);
		//block.CheckHit(&enemy);
		itemManager.CheckHitCharactor(&enemy);

		//Playerのあたり判定
		bombManager.CheckHit(&player);
		map.CheckHitCharactor(&player);
		block.CheckHit(&player);
		itemManager.CheckHitCharactor(&player);

		//PlayerのBomb管理
		bombManager.AddBomb(player);
		bombManager.BombSet(player);
		bombManager.MaintainBomb();

		//EnemyのBomb管理
		enemyBombManager.AddBomb(enemy);
		enemyBombManager.BombSet(enemy);
		enemyBombManager.MaintainBomb();

		//PlayerのBlast管理
		blastManager.Add(player);
		blastManager.FireUp(player);
		blastManager.Set(bombManager);
		blastManager.Maintain(bombManager);
		blastManager.CheckHit(&block, &map, &player, &bombManager, &itemManager);

		//EnemyのBlast管理
		enemyBlastManager.Add(enemy);
		enemyBlastManager.FireUp(enemy);
		enemyBlastManager.Set(enemyBombManager);
		enemyBlastManager.Maintain(enemyBombManager);
		enemyBlastManager.CheckHit(&block, &map, &player, &enemyBombManager, &itemManager);

		//blastManager.CheckHitObject(&map);
		//blastManager.CheckHitObject(&block);
		//blastManager.CheckHitItem(&itemManager);
		//blastManager.CheckHitBomb(&bombManager);
		//blastManager.CheckHitCharactor(&player);
		





		//描画部
		for(int i=0; i<DRAWNUM; ++i)
		{
			//if(i != 6)
			iDraw[i]->Draw();
		}
	
		int color = GetColor(255,255,255);
		int color2 = GetColor(255,0,0);
		int color3 = GetColor(0,0,255);
		DrawFormatString(640,0,color,"ボムアップ獲得数 %d 個",itemManager.GetBombState());
		DrawFormatString(850,0,color,"火力アップ獲得数 %d 個",itemManager.GetFireState());
		DrawFormatString(640,20,color,"フレームタイム　%f　秒",g_frametime);
		DrawFormatString(640,40,color,"出せるボム総数　%d　個",bombManager.size);
		DrawFormatString(640,60,color,"出せるボム数あと　%d　個",bombManager.size-bombManager.GetBombNum());
		
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
		DangerState::GetInstance()->Update();
		for(int i=0; i<MapState::row; ++i)
		{
			for(int j=0; j<MapState::line; ++j)
			{
				DrawFormatString(640+15*j,80+15*i,color,"%d",MapState::GetInstance()->GetState(i,j,BLOCK));
				//DrawFormatString(640+15*j,80+15*i,color,"%d",MapState::GetInstance()->GetDangerState(i, j));			
				//DrawFormatString(640+15*j,80+15*i,color,"%d",DangerState::GetInstance()->node[i][j].danger);				
			}
		}
		//for(int i=0; i<MapState::row; ++i)
		//{
		//	for(int j=0; j<MapState::line; ++j)
		//	{
		//		if(MapState::GetInstance()->GetState(i,j,CHARACTOR) == 1)
		//		DrawFormatString(640+15*j,80+15*i,color3,"%d",MapState::GetInstance()->GetState(i,j,CHARACTOR));
		//		//DrawFormatString(640+15*j,80+15*i,color,"%d",MapState::GetInstance()->GetDangerState(i, j));			
		//		//DrawFormatString(640+15*j,80+15*i,color,"%d",DangerState::GetInstance()->node[i][j].danger);				
		//	}
		//}

		
		//for(int n=0,size=enemy.AI.i_goal.size(); n<size; ++n)
		//{
		//	DrawFormatString(640, 80+15*15+15*n, color, "第%d行", enemy.AI.i_goal[n]);
		//	DrawFormatString(640+15*5, 80+15*15+15*n, color, "第%d列", enemy.AI.j_goal[n]);
		//}

		if(enemy.AI->route->myclass == 1)
			DrawFormatString(0, 32*14,color, "TARGET");
		else if(enemy.AI->route->myclass == 2)
			DrawFormatString(0, 32*14,color, "AVOID");
		
		//if(enemy.AI.rand != -1)
		//	DrawBox(enemy.AI.j_goal[enemy.AI.rand]*32, enemy.AI.i_goal[enemy.AI.rand]*32, enemy.AI.j_goal[enemy.AI.rand]*32+33, enemy.AI.i_goal[enemy.AI.rand]*32+33, color2,FALSE);


		//DrawBox(enemy.AI.j_safe*32, enemy.AI.i_safe*32, enemy.AI.j_safe*32+33, enemy.AI.i_safe*32+33, color3,FALSE);
		
		
		//int n=0;
		//std::list<int>::iterator it = enemy.AI.route.begin();
		/*for (int n=0, size=enemy.AI.route.size(); n<size; ++n)
		{
			switch(enemy.AI.route[n])
			{
			case 1:DrawFormatString(15*4*n, 80+15*15+15*8, color, "LEFT->");continue;
			case 2:DrawFormatString(15*4*n, 80+15*15+15*8, color, "RIGHT->");continue;
			case 3:DrawFormatString(15*4*n, 80+15*15+15*8, color, "UP->");continue;
			case 4:DrawFormatString(15*4*n, 80+15*15+15*8, color, "DOWN->");continue;
			}
		}*/
		


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

	DxLib_End();
	return 0;
}