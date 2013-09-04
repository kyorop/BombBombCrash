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
#include "DxLib.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	ChangeWindowMode(true);
	if(DxLib_Init() == -1)
		return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	
	Map map;
	Player player;
	Bomb bomb;
	ExplosionManager manageExplosion;
	Block block;
	//Item item;
	ItemManager manageItem;

	manageItem.SetItem(block);
	//item.SetItem(block);
	int upfire = 1;
	int count = 0;
	int g_lasttime = 0;
	float g_frametime = 0;

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();

		player.Move();
		player.CheckHit(map);
		block.CheckHit(&player);
		bomb.BombSet(player,map);

		manageItem.CheckHitCharactor(&player);

		if(upfire == 1)
		{
			manageExplosion.AddExplosion(upfire);
			upfire++;
		}
		/*
		if(player.GetStateFire(item) == TRUE && count == 0)
		{
			manageExplosion.AddExplosion(upfire);
			upfire++;
			count++;
		}
		*/
		manageExplosion.SetZahyou(bomb);
		manageExplosion.SetExplosion(bomb);
		manageExplosion.CheckHitObject(&block);//ブロックとのあたり判定//アップキャスト
		manageExplosion.CheckHitObject(&map);//マップブロックとのあたり判定//アップキャスト
		manageExplosion.CheckHitExplosion(&player);//プレイヤーとのあたり判定

		map.DrawMap();
		//item.Draw();
		manageItem.Draw();
		block.Draw();
		bomb.Draw();
		player.Draw(4,map, g_lasttime);
		manageExplosion.DrawExplosion(bomb);
	

		ScreenFlip();
		if(ProcessMessage() == -1)
			break;
	}
	DxLib_End();
	return 0;
}