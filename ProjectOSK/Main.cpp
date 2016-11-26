#include "SceneManger.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;	//�ݒ肵��FPS

bool Update(){
	if (mCount == 0){ //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N){ //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw()
{
	DrawFormatString(500, 500, GetColor(255, 255, 255), "%.1f", mFps);
}

void Wait()
{
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0){
		Sleep(waitTime);	//�ҋ@
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	ChangeWindowMode(true);
	//SetGraphMode(1024,768,16);
	SetGraphMode(800, 600, 16);
	

	if(DxLib_Init() == -1)
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	BombBombCrash::SceneManger sceneMrg;
	
	int g_lasttime = 0;
	float g_frametime = 0;

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();

		Update();
		Draw();

		//*********************************************
		//�v�Z
		sceneMrg.Update();
		sceneMrg.Draw();
		//sceneMrg.PlaySE();

		//*********************************************
		ScreenFlip();

		Wait();

		if(ProcessMessage() == -1)
			break;

	}

	DxLib_End();
	return 0;
}