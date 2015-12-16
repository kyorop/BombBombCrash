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
#include "Drawing.h"
#include "MapFactory.h"
#include "Map.h"

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
	player = std::make_shared<Player>(Player::KEYBORAD);
	map = MapFactory::Craete();
	graphics = std::make_shared<Drawing>();
	timer = std::make_shared<Timer>();
	gameEffect = std::make_shared<GameEffect>(timer);
	Drawing::Add(gameEffect);

	//	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT,GameConst::FIRST_Y_UP)));
	//	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_LEFT, GameConst::FIRST_Y_DOWN)));
	////	enemy.push_back(new CharacterSet(new Enemy(GameConst::FIRST_X_RIGHT, GameConst::FIRST_Y_DOWN)));
	//	enemy.push_back(new CharacterSet(new Enemy(32*8, 32*5)));

	loseTimer = std::make_shared<Timer>();
	winTimer = std::make_shared<Timer>();

	Drawing::Add(player);
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

	graphics->Update();

	//シーン切り替え
	UpdateScene();
}


void Scene_Game::Draw()
{
}

void Scene_Game::PlaySE()
{
	Sound::GetInstance()->PlaySE();
}





GameEffect::GameEffect(const std::shared_ptr<Timer>& timer) :
	white(GetColor(255, 255, 255)),
	x(32 * 20),
	y(32 * 4),
	timer(timer)
{
}

GameEffect::~GameEffect(void)
{
}


void GameEffect::Update()
{

}


void GameEffect::DrawGameEffect()
{

}


void GameEffect::DrawMenuEffect()
{

}

void GameEffect::Draw()
{
	int black = GetColor(255, 255, 255);
	int red = GetColor(255, 0, 0);
	int blue = GetColor(0, 0, 255);
	int deepskyblue = GetColor(0, 191, 255);
	int cannotWalkBlockColor;
	for (int i = 0; i<GameConst::MAP_ROW; ++i)
	{
		for (int j = 0; j<GameConst::MAP_LINE; ++j)
		{
			if (i == 0 || i == 12 || j == 0 || j == 1 || j == 15 || j == 16 || MapState::GetInstance()->GetState(i, j, MapState::MAP) == 1)
				cannotWalkBlockColor = deepskyblue;
			else
				cannotWalkBlockColor = black;

			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i,j,MapState::BOMB));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",MapState::GetInstance()->GetState(i, j, CHARACTOR));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetDangerState(i, j));
			//DrawFormatString(640+15*j,80+15*i,cannotWalkBlockColor,"%d",DangerState::GetInstance()->GetFireState(i, j));
		}
	}
	timer->DrawGraphicalTime(32 * 18 + 10, 10);


	int newBlue = GetColor(0, 119, 182);
	int white = GetColor(255, 255, 255);

	DrawString(x - 82, y - 30, "プレイヤーステータス", newBlue);
	DrawFormatString(x - 39, y, white, "BOMB  LEVEL		%d", MapState::GetInstance()->GetPlayerState()->bombLevel);
	DrawFormatString(x - 39, y + 25, white, "FIRE  LEVEL		%d", MapState::GetInstance()->GetPlayerState()->fireLevel);
	DrawFormatString(x - 39, y + 25 + 25, white, "SPEED LEVEL		%d", MapState::GetInstance()->GetPlayerState()->speedLevel);

	DrawFormatString(32 * 1, 32 * 14, white, "ｚキー　　　爆弾を置く");
	DrawFormatString(32 * 1, 32 * 14 + 30, white, "矢印キー　　各方向へ移動");
}