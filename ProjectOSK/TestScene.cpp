#include "TestScene.h"
#include "Drawing.h"
#include "Image.h"
#include "GameManager.h"
#include "Block.h"
#include "ControlPassingCollision.h"

using namespace BombBombCrash;

TestScene::TestScene() :
player(std::make_shared<Player>(ln::Vector2(32*12, 32), Player::KEYBORAD)),
gameManager(std::make_shared<GameManager>()),
passingCollision(std::make_shared<ControlPassingCollision>())
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	Image::GetInstance()->Initialize();
	gameManager->Initialize();
	gameManager->AddElement(player);

	for (size_t i = 1; i < 8; i+=2)
	{
		for (size_t j = 1; j < 10; j+=2)
		{
			auto block = std::make_shared<Block>(ln::Vector2(32 * j, 32 * i), Image::GetInstance()->GetImage(Image::HARDBLOCK));
			ControlPassingCollision::Add(block);
			gameManager->AddElement(block);
		}
	}

	ControlPassingCollision::Add(static_cast<std::shared_ptr<Character>>(player));

	for (size_t i = 0; i < 10; i++)
	{
		player->IncrementBomb();
	}
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
	player->Update();
	drawer->Update();
	gameManager->Update();
	passingCollision->Update();
}

void TestScene::Draw()
{
	gameManager->Draw();
}


