#include "TestScene.h"
#include "Image.h"
#include "GameManager.h"
#include "Block.h"
#include "ControlPassingCollision.h"
#include "Timer.h"
#include "GameEffect.h"
#include "MapState.h"
#include "MapFactory.h"

using namespace BombBombCrash;

TestScene::TestScene() :
player(std::make_shared<Player>(ln::Vector2(32*13, 32), Player::KEYBORAD)),
gameManager(std::make_shared<GameManager>()),
passingCollision(std::make_shared<ControlPassingCollision>()),
timer(std::make_shared<Timer>()),
gameEffect(std::make_shared<GameEffect>())
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	timer->CountDownRealTime(5 * 60 * 1000);
	MapState::GetInstance()->Initialize();
	Image::GetInstance()->Initialize();
	gameManager->Initialize();
	gameManager->AddElement(gameEffect);

	for (size_t i = 1; i < 8; i+=2)
	{
		for (size_t j = 1; j < 10; j+=2)
		{
			auto map = MapFactory::Create();
			for (auto itr = begin(map); itr != end(map); ++itr)
			{
				gameManager->AddElement(*itr);
				ControlPassingCollision::Add(*itr);
			}
		}
	}
	gameManager->AddElement(player);
	ControlPassingCollision::Add(static_cast<std::shared_ptr<Character>>(player));
}

void TestScene::Finalize()
{
	gameManager->Destroy();
	Image::GetInstance()->Finalize();
}

void TestScene::UpdateScene()
{
}

void TestScene::Update()
{
	gameManager->Update();
	passingCollision->Update();
}

void TestScene::Draw()
{
	gameManager->Draw();
}


