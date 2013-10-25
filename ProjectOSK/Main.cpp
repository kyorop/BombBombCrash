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
#include "CharacterSet.h"
#include <iostream>
#include <vector>
#define DRAWNUM 3
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
	Block block;
	ItemManager itemManager;
	
	CharacterSet player;

	//Player player;
	//BombManager bombManager;
	//BlastManager blastManager;
	
	IDrawable *iDraw[DRAWNUM]=
	{
		&map,
		&itemManager,
		&block,
	};

	int g_lasttime = 0;
	float g_frametime = 0;
	itemManager.SetItem(block);

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();

	
		//ÉLÉÉÉâÇÃà⁄ìÆ
		//player.Move(g_lasttime);
		player.Update();

		//PlayerÇÃÇ†ÇΩÇËîªíË
		//bombManager.CheckHit(&player);
		//map.CheckHitCharactor(&player);
		//block.CheckHit(&player);
		//itemManager.CheckHitCharactor(&player);

		////PlayerÇÃBombä«óù
		//bombManager.AddBomb(player);
		//bombManager.BombSet(player);
		//bombManager.MaintainBomb();

		////PlayerÇÃBlastä«óù
		//blastManager.Add(player);
		//blastManager.FireUp(player);
		//blastManager.Set(bombManager);
		//blastManager.Maintain(bombManager);
		//blastManager.CheckHit(&block, &map, &enemy, &bombManager, &itemManager);
		
		//ï`âÊïî
		for(int i=0; i<DRAWNUM; ++i)
		{
			//if(i != 6)
			iDraw[i]->Draw();
		}

		player.Draw();
		
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;
	}

	DxLib_End();
	return 0;
}