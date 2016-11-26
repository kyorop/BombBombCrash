#include "Scene_Game.h"
#include "Player.h"
#include "GameConstant.h"
#include "MapState.h"
#include "DangerState.h"
#include "Collision.h"
#include "Image.h"
#include "Sound.h"
#include "ISceneChanger.h"
#include "Timer.h"
#include "MapFactory.h"
#include "ControlPassingCollision.h"

using namespace BombBombCrash;

Scene_Game::Scene_Game()
{

}


Scene_Game::~Scene_Game(void)
{
}


void Scene_Game::UpdateScene()
{
	if (timer->CountDownRealTime(5 * 60 * 1000) || CheckHitKey(KEY_INPUT_DELETE))
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
	player = std::make_shared<Player>(ln::Vector2(32,32), Player::KEYBORAD);
//	map = MapFactory::Craete();
	timer = std::make_shared<Timer>();
	passingCollision = std::make_shared<ControlPassingCollision>();

	//	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT,GameConst::FIRST_Y_UP)));
	//	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_LEFT, GameConst::FIRST_Y_DOWN)));
	////	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_DOWN)));
	//	enemy.push_back(new CharacterSet(new Enemy(32*8, 32*5)));

	loseTimer = std::make_shared<Timer>();
	winTimer = std::make_shared<Timer>();

	passingCollision->Add(static_cast<std::shared_ptr<Character>>(player));
}


void Scene_Game::Finalize()
{
	for (int i = 0, size = enemy.size(); i<size; ++i)
	{
		delete enemy[i];
	}
	Sound::GetInstance()->FinalizeForGame();
	Image::GetInstance()->Finalize();
	Collision::Instance()->Finalize();
	DangerState::GetInstance()->Finalize();
	MapState::GetInstance()->Finalize();
}


void Scene_Game::Update()
{
	//ゲーム更新
	MapState::GetInstance()->Update();
	DangerState::GetInstance()->Update();
	player->Update();
	for (int i = 0, size = enemy.size(); i<size; ++i)
	{
		enemy[i]->Update();
	}
	Collision::Instance()->CheckAllCollision();

	passingCollision->Update();

	//シーン切り替え
	UpdateScene();
}


void Scene_Game::Draw()
{
}