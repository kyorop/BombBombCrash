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
#include "Sound.h"
#include "ISceneChanger.h"
#include "Scene_Menu.h"
#include "SceneManger.h"
#include "Timer.h"
#include "GameEffect.h"
#include "DxLib.h"

Scene_Game::Scene_Game()
	:gameScreen(NULL),
	player(NULL),
	enemy(NULL),
	enemy2(NULL),
	enemy3(NULL),
	enemy4(NULL),
	gameEffect(NULL)
{
}


Scene_Game::~Scene_Game(void)
{
}


void Scene_Game::UpdateScene()
{
	if(timer->CountDown(3*60*1000) == true || CheckHitKey(KEY_INPUT_DELETE) == 1)
	{
		sceneMrg->ChangeScene(ISceneChanger::SCENE_MENU);
	}
}


void Scene_Game::Initialize()
{
	Image::GetInstance()->Initialize();
	Sound::GetInstance()->InitializeForGame();
	MapState::GetInstance()->Initialize();
	gameScreen = new GameField;
	player = new CharacterSet(new Player);
	enemy = new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_UP));
	enemy2 = new CharacterSet(new Enemy(GameConst::FIRST_X_LEFT, GameConst::FIRST_Y_DOWN));
	enemy3 = new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_DOWN));
	enemy4 = new CharacterSet(new Enemy(32*8, 32*5));
	timer = new Timer;
	gameEffect = new GameEffect;
}


void Scene_Game::Finalize()
{
	delete gameEffect;
	delete timer;
	delete enemy4;
	delete enemy3;
	delete enemy2;
	delete enemy;
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
	//シーン切り替え
	UpdateScene();

	//ゲーム更新
	MapState::GetInstance()->Update();
	DangerState::GetInstance()->Update();
	gameScreen->Update();
	player->Update();
	enemy->Update();
	enemy2->Update();
	enemy3->Update();
	enemy4->Update();
	Collision::GetInstance()->CheckAllCollision();
	
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

	timer->DrawGraphicalTime(32*18, 10);
	gameEffect->DrawGameEffect();
}

void Scene_Game::PlaySE()
{
	Sound::GetInstance()->PlaySE();
}


