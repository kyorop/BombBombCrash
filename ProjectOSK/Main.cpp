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
#include "Enemy.h"
#include "EnemyBombManager.h"
#include "DxLib.h"
#include <iostream>
#define DRAWNUM 9
#define REGISTERNUM 9
enum object
{
	MAP,
	BLOCK,
	ITEM,
	CHARACTOR,
	BOMB,
	FIRE,
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
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
		&bombManager,
		&enemyBombManager,
		&blastManager,
		&enemyBlastManager,
		&itemManager,
	};


	int g_lasttime = 0;
	float g_frametime = 0;

	//map.Register();
	itemManager.SetItem(block);

	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount() & INT_MAX;
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();

		//�v�Z��

		//�L�����̈ړ�
		player.Move(g_lasttime);
		//enemy.Analyse();
		//enemy.Move(g_lasttime);
		enemy.SetDestination(14,11);

		//Enemy�̂����蔻��
		bombManager.CheckHit(&enemy);
		//map.CheckHitCharactor(&enemy);
		//block.CheckHit(&enemy);
		itemManager.CheckHitCharactor(&enemy);

		//Player�̂����蔻��
		bombManager.CheckHit(&player);
		map.CheckHitCharactor(&player);
		block.CheckHit(&player);
		itemManager.CheckHitCharactor(&player);

		//Player��Bomb�Ǘ�
		bombManager.AddBomb(player);
		bombManager.BombSet(player);
		bombManager.MaintainBomb();

		//Enemy��Bomb�Ǘ�
		enemyBombManager.AddBomb(enemy);
		enemyBombManager.BombSet(enemy);
		enemyBombManager.MaintainBomb();

		
		//Player��Blast�Ǘ�
		blastManager.Add(player);
		blastManager.FireUp(player);
		blastManager.Set(bombManager);
		blastManager.Maintain(bombManager);
		blastManager.CheckHit(&block, &map, &player, &bombManager, &itemManager);


		//Enemy��Blast�Ǘ�
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
		
		//�o�^��
		for(int i=0; i<REGISTERNUM; ++i)
		{
			iRegister[i]->Register();
		}

		//�`�敔
		for(int i=0; i<DRAWNUM; ++i)
		{
		//	if(i != 2)
			iDraw[i]->Draw();
		}
	
		int color = GetColor(255,255,255);
		DrawFormatString(640,0,color,"�{���A�b�v�l���� %d ��",itemManager.GetBombState());
		DrawFormatString(850,0,color,"�ἨA�b�v�l���� %d ��",itemManager.GetFireState());
		DrawFormatString(640,20,color,"�t���[���^�C���@%f�@�b",g_frametime);
		DrawFormatString(640,40,color,"�o����{�������@%d�@��",bombManager.size);
		DrawFormatString(640,60,color,"�o����{�������Ɓ@%d�@��",bombManager.size-bombManager.GetBombNum());
		
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
		//	DrawFormatString(640,80+20*i,color,"[%d]�{���t���O�@%d",i+1,(*bombManager.vbomb)[i]->GetFlag());
		//}

		for(int i=0; i<ROW; ++i)
		{
			for(int j=0; j<LINE; ++j)
			{
				DrawFormatString(640+15*j,80+15*i,color,"%d",MapState::GetInstance()->GetState(i,j,BLOCK));
			}
		}

		for(int n=0,size=enemy.vecGoal.size(); n<size; ++n)
		{
			DrawFormatString(640, 80+15*15+15*n, color, "%d", 3454);
		}
		
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
	enemy.DeleteComponent();
	DxLib_End();
	return 0;
}