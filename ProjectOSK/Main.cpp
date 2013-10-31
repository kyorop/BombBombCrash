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
#include "GameField.h"
#include "Enemy.h"
#include "DangerState.h"
#include <iostream>
#include <vector>
#define REGISTERNUM 7

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	SetGraphMode(1024,768,16);
	ChangeWindowMode(true);
	if(DxLib_Init() == -1)
		return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	
	GameField field;
	CharacterSet playerSet(new Enemy(32*2, 32*1));
	//CharacterSet playerSet(new Player);
	
	int g_lasttime = 0;
	float g_frametime = 0;

	field.Initialize();

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();
		//*********************************************
		//ŒvŽZ
		DangerState::GetInstance()->Update();
		field.Update();
		playerSet.Update();
		Collision::GetInstance()->CheckCollision();

		//•`‰æ•”
		field.Draw();
		playerSet.Draw();


		int black = GetColor(255,255,255);
		int red = GetColor(255,0,0);
		int blue = GetColor(0,0,255);
		int deepskyblue = GetColor(0, 191, 255);
		int cannotWalkBlockColor;
		for(int i=0; i<GameConst::MAP_ROW; ++i)
		{
			for(int j=0; j<GameConst::MAP_LINE; ++j)
			{
				if(i == 0 || i == 12 || j == 0 || j == 1 || j == 15 || j == 16 || MapState::GetInstance()->GetState(i, j, MAP) == 1)
					cannotWalkBlockColor = deepskyblue;
				else
					cannotWalkBlockColor = black;
				//DrawFormatString(640+15*j,80+15*i,black,"%d",MapState::GetInstance()->GetState(i,j,BLOCK));
				//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetDangerState(i, j));
				DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetDangerState(i, j));
				//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetFireState(i, j));
			}
		}
		//*********************************************
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;

	}

	DxLib_End();
	return 0;
}