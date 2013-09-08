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
#include "DxLib.h"
#include <iostream>
#define DRAWNUM 6


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	SetGraphMode(1024,768,16);
	ChangeWindowMode(true);
	if(DxLib_Init() == -1)
		return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	
	Map map;
	Player player;
	ExplosionManager manageExplosion;
	Block block;
	ItemManager itemManager;
	BombManager bombManager;
	BlastManager blastManager;
	IDrawable *iDraw[DRAWNUM]=
	{
		&map,
		&itemManager,
		&block,
		&bombManager,
		&player,
		&blastManager,
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

		//計算
		player.Move(g_lasttime);

		map.CheckHitCharactor(&player);
		//block.CheckHit(&player);

		itemManager.CheckHitCharactor(player);

		bombManager.AddBomb(itemManager);
		bombManager.BombSet(player);
		bombManager.MaintainBomb();
		
		blastManager.Add(itemManager);
		blastManager.FireUp(itemManager);
		blastManager.Set(bombManager);
		blastManager.Maintain();
		//blastManager.CheckHitObject(&block);
		blastManager.CheckHitObject(&map);
		//blastManager.CheckHitCharactor(&player);
		blastManager.CheckHitBomb(&bombManager);

		//描画
		for(int i=0; i<DRAWNUM; ++i)
		{
			if(i != 2)
			iDraw[i]->Draw();
		}
		//map.Draw();
		//manageItem.Draw();
		//block.Draw();
		//bombManager.Draw();
		//player.Draw();
		//blastManager.Draw();
	
		int color = GetColor(255,255,255);
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

		
		for(int i=0,size=bombManager.vbomb->size();i<size;++i)
		{
			DrawFormatString(640,80+20*i,color,"[%d]ボムフラグ　%d",i+1,(*bombManager.vbomb)[i]->GetFlag());
		}
		
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;
	}
	DxLib_End();
	return 0;
}