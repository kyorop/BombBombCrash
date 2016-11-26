#include "GameManager.h"
#include "Image.h"
#include "GameManager.h"
#include "Block.h"
#include "ControlPassingCollision.h"
#include "Timer.h"
#include "GameEffect.h"
#include "MapState.h"
#include "MapFactory.h"
#include "Player.h"
#include "GameObjectManager.h"

using namespace BombBombCrash;

void GameManager::GenerateObjects()
{
	gameObjects->AddElement(gameEffect);

	for (size_t i = 1; i < 8; i += 2)
	{
		for (size_t j = 1; j < 10; j += 2)
		{
			auto map = MapFactory::Create();
			for (auto itr = begin(map); itr != end(map); ++itr)
			{
				gameObjects->AddElement(*itr);
				ControlPassingCollision::Add(*itr);
			}
		}
	}
	gameObjects->AddElement(player);
	ControlPassingCollision::Add(static_cast<std::shared_ptr<Character>>(player));
}

GameManager::GameManager() :
player(std::make_shared<Player>(ln::Vector2(32 * 13, 32), Player::KEYBORAD)),
passingCollision(std::make_shared<ControlPassingCollision>()),
timer(std::make_shared<Timer>()),
gameEffect(std::make_shared<GameEffect>())
{
}

void GameManager::Initialize()
{
	timer->CountDownRealTime(5 * 60 * 1000);
	MapState::GetInstance()->Initialize();
	Image::GetInstance()->Initialize();
	GenerateObjects();
	gameObjects->Initialize();
}

void GameManager::Update()
{
	gameObjects->Update();
	passingCollision->Update();
}

void GameManager::Draw()
{
	gameObjects->Draw();
}

void GameManager::Finalize()
{
	gameObjects->Finalize();
	Image::GetInstance()->Finalize();
}
