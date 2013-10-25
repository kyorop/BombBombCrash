#include "BombManager.h"
#include "ItemManager.h"
#include "MapObstacle.h"
#include "ExplosionManager.h"
#include "Map.h"
#include "Player.h"
#include "Explosion.h"
#include "Bomb.h"
#include "BlastManager.h"
#include "MapState.h"
#include "EnemyBombManager.h"
#include "DxLib.h"
#include "CharacterSet.h"
#include "Collision.h"
#include <iostream>
#include <vector>
#define DRAWNUM 2
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
	ItemManager itemManager;
	CharacterSet playerSet;

	//Player player;
	//BombManager bombManager;
	//BlastManager blastManager;
	
	IDrawable *iDraw[DRAWNUM]=
	{
		&map,
		&itemManager
	};

	int g_lasttime = 0;
	float g_frametime = 0;
	//itemManager.SetItem(block);

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();

		playerSet.Update();
		Collision::GetInstance()->CheckCollision();

		//•`‰æ•”
		for(int i=0; i<DRAWNUM; ++i)
		{
			iDraw[i]->Draw();
		}

		playerSet.Draw();
		
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;
	}

	DxLib_End();
	return 0;
}