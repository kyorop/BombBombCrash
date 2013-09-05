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

	manageItem.SetItem(block);
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
		map.CheckHitCharactor(&player);

		//block.CheckHit(&player);

		manageItem.CheckHitCharactor(player);

		manageBomb.AddBomb(manageItem);
		manageBomb.BombSet(player);
		manageBomb.MaintainBomb();

		blastManager.FireUp(manageItem);
		blastManager.Add(manageItem);
		blastManager.Set(manageBomb);
		blastManager.Maintain();
	
		/*
		manageExplosion.AddExplosion(manageItem);
		manageExplosion.SetExplosion(bomb);
		manageExplosion.CheckHitObject(&block);//�u���b�N�Ƃ̂����蔻��//�A�b�v�L���X�g
		manageExplosion.CheckHitObject(&map);//�}�b�v�u���b�N�Ƃ̂����蔻��//�A�b�v�L���X�g
		manageExplosion.CheckHitExplosion(&player);//�v���C���[�Ƃ̂����蔻��
		*/


		map.Draw();
		
		manageItem.Draw();
		
		//block.Draw();
		
		manageBomb.Draw();
		//bomb.Draw();
		
		player.Draw(map, g_lasttime);
		
		blastManager.Draw();
	
		int color = GetColor(255,255,255);
		DrawFormatString(640,0,color,"�{���A�b�v�l���� %d ��",manageItem.GetBombState());
		DrawFormatString(640,20,color,"�t���[���^�C���@%f�@�b",g_frametime);
		DrawFormatString(640,40,color,"�o����{���������@%d�@��",manageBomb.size);
		DrawFormatString(640,60,color,"�o����{�������Ɓ@%d�@��",manageBomb.size-manageBomb.GetBombNum());


		
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