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
	ItemManager manageItem;
	BombManager manageBomb;
	BlastManager blastManager;

	int g_lasttime = 0;
	float g_frametime = 0;

	manageItem.SetItem(block);
	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();

		//�v�Z
		player.Move(g_lasttime);

		map.CheckHitCharactor(&player);
		//block.CheckHit(&player);

		manageItem.CheckHitCharactor(player);

		manageBomb.AddBomb(manageItem);
		manageBomb.BombSet(player);
		manageBomb.MaintainBomb();
		
		blastManager.Add(manageItem);
		blastManager.FireUp(manageItem);
		blastManager.Set(manageBomb);
		blastManager.Maintain();
		//blastManager.CheckHitObject(&block);
		blastManager.CheckHitObject(&map);
		//blastManager.CheckHitCharactor(&player);
		blastManager.CheckHitBomb(&manageBomb);

		//�`��
		map.Draw();
		
		manageItem.Draw();
		
		//block.Draw();
		
		manageBomb.Draw();
		
		player.Draw();
		
		blastManager.Draw();
	
		int color = GetColor(255,255,255);
		DrawFormatString(640,0,color,"�{���A�b�v�l���� %d ��",manageItem.GetBombState());
		DrawFormatString(850,0,color,"�ἨA�b�v�l���� %d ��",manageItem.GetFireState());
		DrawFormatString(640,20,color,"�t���[���^�C���@%f�@�b",g_frametime);
		DrawFormatString(640,40,color,"�o����{�������@%d�@��",manageBomb.size);
		DrawFormatString(640,60,color,"�o����{�������Ɓ@%d�@��",manageBomb.size-manageBomb.GetBombNum());
		
		//for(int i=0,size=blastManager.vblast->size();i<size;++i)
		//{
		//	for(int j=0,size=(*blastManager.vblast)[i]->vex->size();j<size;++j)
		//	{
		//		DrawFormatString(640+20*i,80+20*j,color,"%d"   , (*(*blastManager.vblast)[i]->vex)[j]->GetX());
		//		//DrawFormatString(640+20*i,80+20*j,color,"%d"   , (*(*blastManager.vblast)[i]->vex)[j]->GetExplosion());
		//		//DrawFormatString(640+20*i,80+20*j,color,"%d"   , (*blastManager.vblast)[i]->vex->size());
		//	}
		//}

		
		for(int i=0,size=manageBomb.vbomb->size();i<size;++i)
		{
			DrawFormatString(640,80+20*i,color,"[%d]�{���t���O�@%d",i+1,(*manageBomb.vbomb)[i]->GetFlag());
		}
		
		ScreenFlip();
		if(ProcessMessage() == -1)
			break;
	}
	DxLib_End();
	return 0;
}