#include "GameManager.h"
#include "Image.h"
#include "GameManager.h"
#include "Block.h"
#include "Timer.h"
#include "GameEffect.h"
#include "MapState.h"
#include "MapFactory.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "ItemManager.h"

using namespace BombBombCrash;

void GameManager::GenerateObjects()
{
	auto map = MapFactory().Create();
//	auto items = ItemManager(map).Create();
	for (auto itr = begin(map); itr != end(map); ++itr)
	{
		gameObjects->AddElement(*itr);
		collisionMng->Add(*itr);
	}
//	for (auto itr = begin(items); itr != end(items); ++itr)
//	{
//		gameObjects->AddElement(*itr);
//		collisionMng->Add(*itr);
//	}
	gameObjects->AddElement(player);
	collisionMng->Add(player);
}

GameManager::GameManager() :
player(std::make_shared<Player>(ln::Vector2(32 * 13, 32), Player::KEYBORAD)),
timer(std::make_shared<Timer>()),
gameEffect(std::make_shared<GameEffect>()),
gameObjects(std::make_shared<GameObjectManager>(this)),
collisionMng(std::make_shared<CollisionManager>())
{
}

void GameManager::Initialize()
{
	timer->CountDownRealTime(5 * 60 * 1000);
	MapState::GetInstance()->Initialize();
	GenerateObjects();
	gameObjects->Initialize();
	collisionMng->Initialize();
}

void GameManager::Update()
{
	gameEffect->Update(*this);
	gameObjects->Update();
	collisionMng->Update();
}

void GameManager::Draw()
{
	gameEffect->Draw(*this);
	gameObjects->Draw();
}

void GameManager::Finalize()
{
	gameObjects->Finalize();
	collisionMng->Finalize();
}

void GameManager::AddGameObject(const std::shared_ptr<CollisionableObject>& object) const
{
	gameObjects->AddElement(object);
	collisionMng->Add(object);
}
