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
#include "DxLib.h"

Scene_Game::Scene_Game()
	:gameScreen(),
	player(),
	enemy(),
	enemy2(),
	enemy3(),
	enemy4()
{
}


Scene_Game::~Scene_Game(void)
{
	//delete gameScreen;
	//delete player;
	//delete enemy;
	//delete enemy2;
	//delete enemy3;
	//delete enemy4;
}


void Scene_Game::UpdateScene()
{
	if(CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		sceneMrg->ChangeScene(ISceneChanger::SCENE_MENU);
	}
}


void Scene_Game::Initialize()
{
	MapState::GetInstance();
	DangerState::GetInstance();
	Collision::GetInstance();
	Image::GetInstance()->Initialize();
	gameScreen = new GameField;
	player = new CharacterSet(new Player);
	enemy = new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_UP));
	enemy2 = new CharacterSet(new Enemy(GameConst::FIRST_X_LEFT, GameConst::FIRST_Y_DOWN));
	enemy3 = new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_DOWN));
	enemy4 = new CharacterSet(new Enemy(32*8, 32*5));
}


void Scene_Game::Finalize()
{
	delete enemy4;
	delete enemy3;
	delete enemy2;
	delete enemy;
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
	DangerState::GetInstance()->Update();
	gameScreen->Update();
	player->Update();
	enemy->Update();
	enemy2->Update();
	enemy3->Update();
	enemy4->Update();
	Collision::GetInstance()->CheckCollision();
	
}


void Scene_Game::Draw()
{
	gameScreen->Draw();
	player->Draw();
	enemy->Draw();
	enemy2->Draw();
	enemy3->Draw();
	enemy4->Draw();

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

			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i,j,MAP));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i, j, CHARACTOR));
			DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetDangerState(i, j));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetFireState(i, j));
		}
	}
}



