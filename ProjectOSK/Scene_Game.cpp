#include "Scene_Game.h"
#include "GameField.h"
#include "Player.h"
#include "GameConstant.h"
#include "MapState.h"
#include "DangerState.h"
#include "Collision.h"
#include "Image.h"
#include "Sound.h"
#include "ISceneChanger.h"
#include "Timer.h"

Scene_Game::Scene_Game()
	:gameScreen(NULL),
	player(NULL),
	enemy(NULL),
	gameEffect(NULL)
{
	
}


Scene_Game::~Scene_Game(void)
{
}


void Scene_Game::UpdateScene()
{
	if(timer->CountDownRealTime(5*60*1000) == true || CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		sceneMrg->ChangeScene(ISceneChanger::SCENE_MENU);
	}
	//else if(MapState::GetInstance()->GetPlayerState()->flag == 0)
	//{
	//	if(loseTimer->CountDownFrame(3*1000))
	//	{
	//		Scene_Score::SetResult(Scene_Score::LOSE);
	//		sceneMrg->ChangeScene(ISceneChanger::SCENE_SCORE);
	//	}
	//}
	//else if(MapState::GetInstance()->GetEnemyNum() == 0)
	//{
	//	if(winTimer->CountDownFrame(3*1000))
	//	{
	//		Scene_Score::SetResult(Scene_Score::WIN);
	//		sceneMrg->ChangeScene(ISceneChanger::SCENE_SCORE);
	//	}
	//}

}


void Scene_Game::Initialize()
{
	Image::GetInstance()->Initialize();
	Sound::GetInstance()->InitializeForGame();
	MapState::GetInstance()->Initialize();
	gameScreen = new GameField();
	player = new Player(Player::KEYBORAD);
//	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT,GameConst::FIRST_Y_UP)));
//	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_LEFT, GameConst::FIRST_Y_DOWN)));
////	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_DOWN)));
//	enemy.push_back(new CharacterSet(new Enemy(32*8, 32*5)));
	timer = new Timer();
	loseTimer = new Timer();
	winTimer = new Timer();
	gameEffect = new GameEffect();
}


void Scene_Game::Finalize()
{
	delete gameEffect;
	delete winTimer;
	delete loseTimer;
	delete timer;
	for (int i=0,size=enemy.size(); i<size; ++i)
	{
		delete enemy[i];
	}
	delete player;
	delete gameScreen;
	Sound::GetInstance()->FinalizeForGame();
	Image::GetInstance()->Finalize();
	Collision::GetInstance()->Finalize();
	DangerState::GetInstance()->Finalize();
	MapState::GetInstance()->Finalize();
}


void Scene_Game::Update()
{
	//ゲーム更新
	MapState::GetInstance()->Update();
	DangerState::GetInstance()->Update();
	gameScreen->Update();
	player->Update();
	for (int i=0,size=enemy.size(); i<size; ++i)
	{
		enemy[i]->Update();
	}
	Collision::GetInstance()->CheckAllCollision();
	
	//シーン切り替え
	UpdateScene();
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
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetDangerState(i, j));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetFireState(i, j));
		}
	}

	gameEffect->DrawGameEffect();
	timer->DrawGraphicalTime(32*18+10, 10);
}

void Scene_Game::PlaySE()
{
	Sound::GetInstance()->PlaySE();
}



//**-----------------------------------------------------------

GameEffect::GameEffect(void)
	:white(GetColor(255,255,255)),
	x(32*20),
	y(32*4)
//	bomb(new BombController())
{
	for (int i = 0; i < 10; i++)
	{
//		bomb->Add();
	}	
	
}


GameEffect::~GameEffect(void)
{
//	delete bomb;
}


void GameEffect::Update()
{
	
}


void GameEffect::DrawGameEffect()
{
	int blue = GetColor(0,119,182);
	int white = GetColor(255,255,255);

	DrawString(x-82, y-30,"プレイヤーステータス",blue);
	DrawFormatString(x-39, y, white, "BOMB  LEVEL		%d", MapState::GetInstance()->GetPlayerState()->bombLevel);
	DrawFormatString(x-39, y+25, white, "FIRE  LEVEL		%d", MapState::GetInstance()->GetPlayerState()->fireLevel);
	DrawFormatString(x-39, y+25+25, white, "SPEED LEVEL		%d", MapState::GetInstance()->GetPlayerState()->speedLevel);

	DrawFormatString(32*1, 32*14, white, "ｚキー　　　爆弾を置く");
	DrawFormatString(32*1, 32*14+30, white, "矢印キー　　各方向へ移動");
}


void GameEffect::DrawMenuEffect()
{

}