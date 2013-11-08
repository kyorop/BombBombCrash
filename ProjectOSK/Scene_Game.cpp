#include "Scene_Game.h"
#include "GameField.h"
#include "CharacterSet.h"
#include "Player.h"
#include "Enemy.h"
#include "GameConstant.h"
#include "MapState.h"
#include "DangerState.h"
#include "Collision.h"
#include "Image.h"
#include "ISceneChanger.h"
#include "Scene_Menu.h"
#include "SceneManger.h"
#include "Timer.h"
#include "EnemyAI.h"
#include "DxLib.h"

Scene_Game::Scene_Game()
	:gameScreen(),
	player(),
	enemy()
{
	
}


Scene_Game::~Scene_Game(void)
{
}


void Scene_Game::UpdateScene()
{
	if(timer->CountDownRealTime(300000) == true || CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		sceneMrg->ChangeScene(ISceneChanger::SCENE_MENU);
	}
}


void Scene_Game::Initialize()
{
	Image::GetInstance()->Initialize();
	//MapState::GetInstance();
	//DangerState::GetInstance();
	//Collision::GetInstance();
	gameScreen = new GameField;
	player = new CharacterSet(new Player);
	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT,GameConst::FIRST_Y_DOWN)));
	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT,GameConst::FIRST_Y_UP)));
	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_LEFT,GameConst::FIRST_Y_DOWN)));
	enemy.push_back(new CharacterSet(new Enemy(32*8, 32*5)));
	timer = new Timer;
}


void Scene_Game::Finalize()
{
	delete timer;
	for (int i=0,size=enemy.size(); i<size; ++i)
	{
		delete enemy[i];
	}
	delete player;
	delete gameScreen;
	Image::GetInstance()->Finalize();
	Collision::GetInstance()->Finalize();
	DangerState::GetInstance()->Finalize();
	MapState::GetInstance()->Finalize();
}


void Scene_Game::Update()
{
	//シーン切り替え
	UpdateScene();

	//ゲーム更新
	MapState::GetInstance()->Update();
	DangerState::GetInstance()->Update();
	gameScreen->Update();
	player->Update();
	for (int i=0,size=enemy.size(); i<size; ++i)
	{
		enemy[i]->Update();
	}
	Collision::GetInstance()->CheckCollision();
	
}


void Scene_Game::Draw()
{
	gameScreen->Draw();
	player->Draw();
	for (int i=0,size=enemy.size(); i<size; ++i)
	{
		enemy[i]->Draw();
	}

	int black = GetColor(255,255,255);
	int red = GetColor(255,0,0);
	int blue = GetColor(0,0,255);
	int deepskyblue = GetColor(0, 191, 255);
	int cannotWalkBlockColor;
	for(int i=0; i<GameConst::MAP_ROW; ++i)
	{
		for(int j=0; j<GameConst::MAP_LINE; ++j)
		{
			if(i == 0 || i == 12 || j == 0 || j == 1 || j == 15 || j == 16 || MapState::GetInstance()->GetState(i, j, MapState::MAP) == 1)
				cannotWalkBlockColor = deepskyblue;
			else
				cannotWalkBlockColor = black;

			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i,j,MapState::BOMB));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i, j, CHARACTOR));
			DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetDangerState(i, j));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetFireState(i, j));
		}
	}

	//EnemyAI::ShowState(640,0);

	int currentMilliSecond = timer->GetLeftedTime();		//残り時間(ミリ秒)
	int minute = currentMilliSecond / (60*1000);		//残り時間(分)
	int second = (currentMilliSecond - ( (60 * minute) * 1000))/1000;		//残り時間(秒)
	
	int haba = 0;
	if(second < 10)
	{
		haba = 9;
		DrawFormatString(640, 65, red, "%d", 0);
	}
	DrawFormatString(640, 50, red, "%d", minute);
	DrawFormatString(640+haba, 65, red, "%d", second);

}



