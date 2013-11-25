#include "SceneManger.h"
#include "DxLib.h"
#include <stdio.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	ChangeWindowMode(true);
	//SetGraphMode(1024,768,16);
	SetGraphMode(800, 600, 16);
	

	if(DxLib_Init() == -1)
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);
	
	SceneManger sceneMrg;
	
	int g_lasttime = 0;
	float g_frametime = 0;

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();
		//*********************************************
		//ŒvŽZ
		sceneMrg.Update();
		sceneMrg.Draw();
		//sceneMrg.PlaySE();

		//*********************************************
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;

	}

	DxLib_End();
	return 0;
}